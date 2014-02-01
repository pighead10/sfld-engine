#pragma once

#include "stdafx.h"

typedef std::map<std::string, void*> MessageInfo;

class ComponentMessage{
public:
	enum MessageCategory{
		CATEGORY_PHYSICS,
		CATEGORY_AI,
		CATEGORY_MISC,
		//add more...
	};

	enum MessageType{
		PHYSICS_COLLISION,
		MISC,
		//add more...
	};

	ComponentMessage(){}
	ComponentMessage(MessageCategory messageCategory, MessageType messageType, MessageInfo messageInfo)
		: messageCategory_(messageCategory), messageType_(messageType), messageInfo_(messageInfo){}


	MessageCategory getMessageCategory() const{
		return messageCategory_;
	}

	MessageType getMessageType() const{
		return messageType_;
	}

	MessageInfo getMessageInfo() const{
		return messageInfo_;
	}

private:
	MessageCategory messageCategory_;
	MessageType messageType_;
	MessageInfo messageInfo_;
};