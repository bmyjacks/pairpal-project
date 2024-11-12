#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

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
    Message();

    explicit Message(MessageType type, const std::string&content);

    explicit Message(const std::string&json);

    ~Message();

    [[nodiscard]] std::string toJson() const;

private:
    MessageType type_;
};


#endif //MESSAGE_HPP
