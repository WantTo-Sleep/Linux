#ifndef __M_MATCHER_H
#define __M_MATCHER_H

#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "util.hpp"
#include "online.hpp"
#include "room.hpp"

namespace sjx
{
    template <typename T>
    class match_queue
    {
    private:
        // 用链表而不直接使用queue是因为有中间删除数据的需要
        std::list<T> _list;
        // 实现线程安全
        std::mutex _mutex;
        // 主要为了阻塞消费者，后边使用的时候，队列中元素个数<2则阻塞
        std::condition_variable _cond;

    public:
        int size()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            return _list.size();
        }
        bool empty()
        {
            //std::unique_lock<std::mutex> lock(_mutex);
            return _list.empty();
        }
        void wait()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cond.wait(lock);
        }
        void push(const T &data)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.push_back(data);
            _cond.notify_all();
        }
        bool pop(T &data)
        {
            if (_list.empty() == true)
            {
                return false;
            }
            std::unique_lock<std::mutex> lock(_mutex);
            data = _list.front();
            _list.pop_front();
            return true;
        }
        void remove(T &data)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _list.remove(data);
        }
    };

    class matcher
    {
    private:
        match_queue<uint64_t> _q_normal; // 普通选手匹配队列
        match_queue<uint64_t> _q_high;   // 高手匹配队列
        match_queue<uint64_t> _q_super;  // 大神匹配队列
        std::thread _th_normal;
        std::thread _th_high;
        std::thread _th_super;
        room_manager *_rm;
        user_table *_ut;
        online_manager *_om;

        void handle_match(match_queue<uint64_t> &mq)
        {
            while (1)
            {
                // 1.判断队列人数是否大于2，小于2则阻塞等待
                while (mq.size() < 2)
                {
                    mq.wait();
                }
                // 2.出队两个玩家
                uint64_t uid1, uid2;
                bool ret = mq.pop(uid1);
                if (ret == false)
                {
                    continue;
                }
                ret = mq.pop(uid2);
                if (ret == false)
                {
                    this->add(uid1);
                    continue;
                }
                // 3.校验两个玩家是否在线
                wsserver_t::connection_ptr conn1 = _om->get_conn_from_hall(uid1);
                if (conn1.get() == nullptr)
                {
                    this->add(uid2);
                    continue;
                }
                wsserver_t::connection_ptr conn2 = _om->get_conn_from_hall(uid2);
                if (conn2.get() == nullptr)
                {
                    this->add(uid1);
                    continue;
                }
                // 4.为两个玩家创建房间，并将玩家加入房间中
                room_ptr rp = _rm->create_room(uid1, uid2);
                if (rp.get() == nullptr)
                {
                    this->add(uid1);
                    this->add(uid2);
                    continue;
                }
                // 5.对两个玩家进行响应
                Json::Value resp;
                resp["optype"] = "match_success";
                resp["result"] = true;
                std::string body;
                json_util::serialize(resp, body);
                conn1->send(body);
                conn2->send(body);
            }
        }

        void th_normal_entry() { handle_match(_q_normal); }
        void th_high_entry() { handle_match(_q_normal); }
        void th_super_entry() { handle_match(_q_normal); }

    public:
        matcher(room_manager *rm, user_table *ut, online_manager *om)
            : _rm(rm), _ut(ut), _om(om),
              _th_normal(std::thread(&matcher::th_normal_entry, this)),
              _th_high(std::thread(&matcher::th_high_entry, this)),
              _th_super(std::thread(&matcher::th_super_entry, this))
        {
            DLOG("游戏匹配模块初始化完毕...");
        }
        bool add(uint64_t uid)
        {
            // 根据玩家的天梯分数，来判定玩家等级，添加到不同的匹配队列
            // 1.根据用户ID，获取玩家信息
            Json::Value user;
            bool ret = _ut->select_by_id(uid, user);
            if (ret == false)
            {
                DLOG("获取玩家: %d 信息失败！", uid);
                return false;
            }
            int score = user["score"].asInt();
            // 2.添加到指定的队列中
            if (score < 2000)
                _q_normal.push(uid);
            else if (score >= 2000 && score < 3000)
                _q_high.push(uid);
            else
                _q_super.push(uid);
            return true;
        }
        bool del(uint64_t uid)
        {
            // 1.根据用户ID，获取玩家信息
            Json::Value user;
            bool ret = _ut->select_by_id(uid, user);
            if (ret == false)
            {
                DLOG("获取玩家: %d 信息失败！", uid);
                return false;
            }
            int score = user["score"].asInt();
            // 2.从指定的队列中移除
            if (score < 2000)
                _q_normal.remove(uid);
            else if (score >= 2000 && score < 3000)
                _q_high.remove(uid);
            else
                _q_super.remove(uid);
            return true;
        }
    };
}

#endif