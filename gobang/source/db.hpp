#ifndef __M_DB_H__
#define __M_DB_H__

#include <mutex>
#include <cassert>

#include "util.hpp"

namespace sjx
{
    class user_table
    {
    private:
        MYSQL *_mysql;     // mysql操作句柄
        std::mutex _mutex; // 互斥锁保护数据库的访问操作
    public:
        user_table(const std::string &host, const std::string &username, const std::string &password, const std::string &dbname, uint16_t port = 3306)
        {
            _mysql = mysql_util::mysql_create(host, username, password, dbname, port);
            assert(_mysql != nullptr);
        }
        ~user_table()
        {
            mysql_util::mysql_destroy(_mysql);
            _mysql = nullptr;
        }
        // 注册时新增用户
        bool insert(Json::Value &user)
        {
#define INSERT_USER "insert user values(null, '%s', password('%s'), 1000, 0, 0);"
            if (user["password"].isNull() || user["username"].isNull())
            {
                DLOG("INPUT USERNAME OR PASSWORD");
                return false;
            }
            char sql[1024] = {0};
            sprintf(sql, INSERT_USER, user["username"].asCString(), user["password"].asCString());
            {
                std::unique_lock<std::mutex> lock(_mutex);
                bool ret = mysql_util::mysql_exec(_mysql, sql);
                if (ret == false)
                {
                    ELOG("insert user info failed!");
                    return false;
                }
            }
            return true;
        }
        // 登陆验证，并返回详细的用户信息
        bool login(Json::Value &user)
        {
#define LOGIN_USER "select id, score, total_count, win_count from user where username='%s' and password=password('%s');"
            if (user["password"].isNull() || user["username"].isNull())
            {
                DLOG("INPUT USERNAME OR PASSWORD");
                return false;
            }
            char sql[1024] = {0};
            sprintf(sql, LOGIN_USER, user["username"].asCString(), user["password"].asCString());
            MYSQL_RES *res = nullptr;
            {
                std::unique_lock<std::mutex> lock(_mutex);
                bool ret = mysql_util::mysql_exec(_mysql, sql);
                if (ret == false)
                {
                    DLOG("user login failed!");
                    return false;
                }

                res = mysql_store_result(_mysql);
                if (res == nullptr)
                {
                    DLOG("have no login user info!");
                    return false;
                }
            }
            int row_num = mysql_num_rows(res);
            if (row_num != 1)
            {
                DLOG("user info queried is not unique!");
                return false;
            }
            MYSQL_ROW row = mysql_fetch_row(res);
            user["id"] = (Json::UInt64)std::stol(row[0]);
            user["score"] = (Json::Int64)std::stol(row[1]);
            user["total_count"] = (Json::UInt)std::stoi(row[2]);
            user["win_count"] = (Json::UInt)std::stoi(row[3]);
            mysql_free_result(res);
            return true;
        }
        // 通过用户名获取用户信息
        bool select_by_name(const std::string &name, Json::Value &user)
        {
#define USER_BY_NAME "select id, score, total_count, win_count from user where username='%s';"
            char sql[1024] = {0};
            sprintf(sql, USER_BY_NAME, name.c_str());
            MYSQL_RES *res = nullptr;
            {
                std::unique_lock<std::mutex> lock(_mutex);
                bool ret = mysql_util::mysql_exec(_mysql, sql);
                if (ret == false)
                {
                    DLOG("get user by name failed!");
                    return false;
                }
                res = mysql_store_result(_mysql);
                if (res == nullptr)
                {
                    DLOG("have no login user info!");
                    return false;
                }
            }
            int row_num = mysql_num_rows(res);
            if (row_num != 1)
            {
                DLOG("user info queried is not unique!");
                return false;
            }
            MYSQL_ROW row = mysql_fetch_row(res);
            user["id"] = (Json::UInt64)std::stol(row[0]);
            user["username"] = name;
            user["score"] = (Json::Int64)std::stol(row[1]);
            user["total_count"] = (Json::UInt)std::stoi(row[2]);
            user["win_count"] = (Json::UInt)std::stoi(row[3]);
            mysql_free_result(res);
            return true;
        }
        // 通过id获取用户信息
        bool select_by_id(uint64_t id, Json::Value &user)
        {
#define USER_BY_ID "select username, score, total_count, win_count from user where id='%d';"
            char sql[1024] = {0};
            sprintf(sql, USER_BY_ID, id);
            MYSQL_RES *res = nullptr;
            {
                std::unique_lock<std::mutex> lock(_mutex);
                bool ret = mysql_util::mysql_exec(_mysql, sql);
                if (ret == false)
                {
                    DLOG("get user by id failed!");
                    return false;
                }
                res = mysql_store_result(_mysql);
                if (res == nullptr)
                {
                    DLOG("have no login user info!");
                    return false;
                }
            }
            int row_num = mysql_num_rows(res);
            if (row_num != 1)
            {
                DLOG("user info queried is not unique!");
                return false;
            }
            MYSQL_ROW row = mysql_fetch_row(res);
            user["id"] = (Json::UInt64)id;
            user["username"] = row[0];
            user["score"] = (Json::Int64)std::stol(row[1]);
            user["total_count"] = (Json::UInt)std::stoi(row[2]);
            user["win_count"] = (Json::UInt)std::stoi(row[3]);
            mysql_free_result(res);
            return true;
        }
        // 胜利时天体分数增加30，战斗场次增加1，胜利场次增加
        bool win(uint64_t id)
        {
#define USER_WIN "update user set score=score+30, total_count=total_count+1, win_count=win_count+1 where id=%d;"
            char sql[1024] = {0};
            sprintf(sql, USER_WIN, id);
            std::unique_lock<std::mutex> lock(_mutex);
            bool ret = mysql_util::mysql_exec(_mysql, sql);
            if (ret == false)
            {
                DLOG("update win user info failed!");
                return false;
            }
            return true;
        }
        // 失败是天体分数减少30，战斗场次增加1，其他不变
        bool lose(uint64_t id)
        {
#define USER_LOSE "update user set score=score-30, total_count=total_count+1 where id=%d;"
            char sql[1024] = {0};
            sprintf(sql, USER_LOSE, id);
            std::unique_lock<std::mutex> lock(_mutex);
            bool ret = mysql_util::mysql_exec(_mysql, sql);
            if (ret == false)
            {
                DLOG("update lose user info failed!");
                return false;
            }
            return true;
        }
    };
}

#endif