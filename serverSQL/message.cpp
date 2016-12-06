
//********************************************************
//
//       FileName:      message.cpp
//
//       Author:  huobingli - huobingli@outlook.com
//       Description:    
//       Create: 2016-12-05  14:40:37
//       Last Modified: 2016-12-05 14:40:37
//********************************************************
// 
#include <iostream>

#include <vector>

#ifndef
#define
class Message{
	public:
		uint8_t connection_type;
		uint16_t data_length;
		uint8_t channel;
		uint8_t direction;
		uint32_t source_id;
		uint32_t destination_id;
		uint8_t cmd_type;
		uint8_t status;
		std::vector<char> data;
		uint16_t check_sum;
		~Message(){
		}
};

#endif
