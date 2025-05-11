#include "crow.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <cstdlib>

using json = nlohmann::json;
std::unordered_map<std::string, std::string> sessionMap;

json read_json(const std::string &path)
{
    std::ifstream file(path);
    json data = json::array();
    if (file.is_open())
    {
        file >> data;
    }
    return data;
}

void write_json(const std::string &path, const json &data)
{
    std::ofstream file(path);
    file << data.dump(4);
}

std::string generate_token(const std::string username)
{
    return "token_" + username + "_123";
}

bool is_authenticated(const crow::request &req, std::string &username)
{
    auto auth = req.get_header_value("Authorization");
    const std::string prefix = "Bearer ";
    if (auth.rfind(prefix, 0) == 0)
    {
        auth = auth.substr(prefix.length());
    }

    for (auto &[user, token] : sessionMap)
    {
        if (token == auth)
        {
            username = user;
            return true;
        }
    }
    return false;
}

int main()
{
    crow::SimpleApp app;

    // ------------------ REGISTER ------------------
    CROW_ROUTE(app, "/register").methods("POST"_method)([](const crow::request &req)
                                                        {
        auto body = crow::json::load(req.body);
        if (!body)
        {
            crow::json::wvalue res;
            res["message"] = "Invalid JSON";
            return crow::response(400, res);
        }

        auto users = read_json("users.json");
        for (auto &user : users)
        {
            if (user["username"].get<std::string>() == body["username"].s())
            {
                crow::json::wvalue res;
                res["message"] = "User already exists";
                return crow::response(400, res);
            }
        }

        users.push_back({
            {"username", body["username"].s()},
            {"password", body["password"].s()}
        });

        write_json("users.json", users);
        crow::json::wvalue res;
        res["message"] = "User registered";
        return crow::response(200, res); });

    // ------------------ LOGIN ------------------
    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request &req)
                                                     {
        auto body = crow::json::load(req.body);
        if (!body)
        {
            crow::json::wvalue res;
            res["message"] = "Invalid JSON";
            return crow::response(400, res);
        }

        auto users = read_json("users.json");
        for (auto &user : users)
        {
            if (user["username"].get<std::string>() == body["username"].s() &&
                user["password"].get<std::string>() == body["password"].s())
            {
                std::string token = generate_token(user["username"]);
                sessionMap[user["username"]] = token;
                crow::json::wvalue res;
                res["message"] = token;
                return crow::response(200, res);
            }
        }

        crow::json::wvalue res;
        res["message"] = "Invalid credentials";
        return crow::response(401, res); });

    // ------------------ ADD NOTE ------------------
    CROW_ROUTE(app, "/note").methods("POST"_method)([](const crow::request &req)
                                                    {
        std::string username;
        if (!is_authenticated(req, username))
        {
            crow::json::wvalue res;
            res["message"] = "Unauthorized";
            return crow::response(401, res);
        }

        auto body = crow::json::load(req.body);
        if (!body.has("content"))
        {
            crow::json::wvalue res;
            res["message"] = "Invalid note";
            return crow::response(400, res);
        }

        auto notes = read_json("notes.json");
        notes.push_back({{"user", username}, {"content", body["content"].s()}});
        write_json("notes.json", notes);

        crow::json::wvalue res;
        res["message"] = "Note added";
        return crow::response(200, res); });

    // ------------------ GET NOTES ------------------
    CROW_ROUTE(app, "/note").methods("GET"_method)([](const crow::request &req)
                                                   {
        std::string username;
        if (!is_authenticated(req, username))
        {
            crow::json::wvalue res;
            res["message"] = "Unauthorized";
            return crow::response(401, res);
        }

        auto notes = read_json("notes.json");
        json user_notes = json::array();
        for (auto &note : notes)
        {
            if (note["user"] == username)
                user_notes.push_back(note);
        }

        crow::json::wvalue res;
        res["notes"] = crow::json::load(user_notes.dump());
        return crow::response(200, res); });

    // ------------------ DELETE NOTES ------------------
    CROW_ROUTE(app, "/note").methods("DELETE"_method)([](const crow::request &req)
                                                      {
        std::string username;
        if (!is_authenticated(req, username))
        {
            crow::json::wvalue res;
            res["message"] = "Unauthorized";
            return crow::response(401, res);
        }

        auto notes = read_json("notes.json");
        json filtered = json::array();
        for (auto &note : notes)
        {
            if (note["user"] != username)
                filtered.push_back(note);
        }

        write_json("notes.json", filtered);
        crow::json::wvalue res;
        res["message"] = "Notes deleted";
        return crow::response(200, res); });

    int port = 18080;
    if (const char* env_p = std::getenv("PORT")) {
        port = std::stoi(env_p);
    }
    app.port(port).multithreaded().run();
}
