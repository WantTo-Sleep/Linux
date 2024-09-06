#include "server.hpp"

#define HOST "127.0.0.1"
#define PORT 3306
#define USER "root"
#define PASS "123456"
#define DBNAME "gobang"

void mysql_test()
{
    MYSQL *mysql = sjx::mysql_util::mysql_create(HOST, USER, PASS, DBNAME, PORT);
    const char *sql = "insert stu values(null, '小黑', 18, 53, 68, 87);";
    bool ret = sjx::mysql_util::mysql_exec(mysql, sql);
    if (ret == false)
    {
        return;
    }
    sjx::mysql_util::mysql_destroy(mysql);
}

void json_test()
{
    Json::Value root;
    std::string body;
    root["姓名"] = "小明";
    root["年龄"] = 18;
    root["成绩"].append(10);
    root["成绩"].append(20.5);
    root["成绩"].append(30);
    sjx::json_util::serialize(root, body);
    DLOG("%s", body.c_str());

    Json::Value val;
    sjx::json_util::unserialize(body, val);
    std::cout << "姓名: " << val["姓名"].asString() << std::endl;
    std::cout << "年龄: " << val["年龄"].asInt() << std::endl;
    int sz = val["成绩"].size();
    for (int i = 0; i < sz; ++i)
    {
        std::cout << "成绩: " << val["成绩"][i].asFloat() << std::endl;
    }
}

void str_test()
{
    std::string str = ",,...,,123,234,,,,345,,,";
    std::vector<std::string> arry;
    sjx::string_util::split(str, ",", arry);
    for (auto &e : arry)
    {
        DLOG("%s", e.c_str());
    }
}

void file_test()
{
    std::string filename = "./makefile";
    std::string body;
    sjx::file_util::read(filename, body);

    DLOG("%s", body.c_str());
}

void db_test()
{
    sjx::user_table ut(HOST, USER, PASS, DBNAME, PORT);
    Json::Value user;
    user["username"] = "xiaoming";
    // user["password"] = "1231234";
    bool ret = ut.win(1);
    // std::string body;
    // sjx::json_util::serialize(user, body);
    // DLOG("%s", body.c_str());
}

void online_test()
{
    sjx::online_manager om;
    wsserver_t::connection_ptr conn;
    uint64_t uid = 2;
    om.enter_game_room(uid, conn);
    if (om.is_in_game_room(uid))
    {
        DLOG("IN GAME HALL");
    }
    else
    {
        DLOG("NOT IN GAME HALL");
    }
    om.exit_game_room(uid);
    if (om.is_in_game_room(uid))
    {
        DLOG("IN GAME HALL");
    }
    else
    {
        DLOG("NOT IN GAME HALL");
    }
}

void room_test()
{
    sjx::user_table ut(HOST, USER, PASS, DBNAME, PORT);
    sjx::online_manager om;

    // sjx::room r(10, &ut, &om);
    sjx::room_manager rm(&ut, &om);
    sjx::room_ptr rp = rm.create_room(10, 20);
    sjx::matcher mc(&rm, &ut, &om);
}

int main()
{
    // room_test();
    sjx::gobang_server _server(HOST, USER, PASS, DBNAME, PORT);
    _server.start(8888);
    return 0;
}
