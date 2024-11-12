#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <nlohmann/json.hpp>

enum class MessageType {
    UNKNOWN,
    ADD_USER,
    REMOVE_USER,
    USER_EXISTS,
    GET_USER,
    AUTHENTICATE,
    ADD_USER_TAG,
    REMOVE_USER_TAG,
    GET_USER_TAGS,
};

class Message {
public:
    explicit Message(MessageType type, nlohmann::json content);

    explicit Message(const nlohmann::json&json);

    ~Message();

    [[nodiscard]] MessageType getType() const;

    [[nodiscard]] nlohmann::json getContent() const;

    [[nodiscard]] nlohmann::json toJson() const;

private:
    MessageType type_;
    nlohmann::json content_;
};


#endif //MESSAGE_HPP
