#include "balboa_messages.hpp"

using namespace balboa;

void ControlConfigRequest::SetPayload(
	bool isType1, data_type &data)
{
	if (isType1)
	{
		data.payload[0] = 0x02;
		data.payload[1] = 0x00;
		data.payload[2] = 0x00;
	}
	else
	{
		data.payload[0] = 0x00;
		data.payload[1] = 0x00;
		data.payload[2] = 0x01;
	}
}

void ToggleItemRequest::Toggle(ToggleItemRequest::ToggleItem item,
 data_type &data)
{
	data._item = item;
	data._r = 0;
}

void SetTempRequest::SetTemperature(SpaTemp &temp, data_type &data)
{
	data._temp = temp.temp;
}

void SetTimeRequest::SetTime(SpaTime &time, data_type &data)
{
	data._hour = time.hour;
	data._displayAs24Hr = time.displayAs24Hr;
	data._minute = time.minute;
}

void FilterConfigRequest::SetPayload(data_type &data)
{
	data._payload[0] = 0x01;
	data._payload[1] = 0;
	data._payload[2] = 0;
}

void SetTempScaleRequest::SetScale(bool isCelsius, data_type &data)
{
	data._scale = isCelsius;
}

#if 0
balboa::MessageBase::MessageBase(size_t size, unsigned long messageType)
{
	_prefix = '\x7e';
	_length = size - 2;
	_messageType = messageType & 0x00ffffff;
}


void balboa::MessageBase::Dump() const
{
	Dump(_length + 2);
}

void balboa::MessageBase::Dump(size_t size) const
{
	uint8_t *pStart = (uint8_t *)this;

	Serial.print(F("Dump - # bytes: "));
	Serial.println(size);

	for (size_t i = 0; i < size; i++)
	{
		if (pStart[i] < 0x10)
		{
			Serial.print('0');
		}
		Serial.print(pStart[i], HEX), Serial.print(' ');
	}

	if (size > 0) Serial.println();
}

void 
balboa::MessageBase::SetCRC()
{
	*(((uint8_t *)this) + (this->_length)) = CalcCRC();
}

bool
balboa::MessageBase::CheckCRC() const
{
	return (*(((uint8_t *)this) + (this->_length)) == CalcCRC());
}


uint8_t
balboa::MessageBase::CalcCRC() const
{
	return F_CRC_CalculaCheckSum(&_length, _length - 1);
}



balboa::MessageSuffix::MessageSuffix()
{
	_check = 0xff;
	_suffix = '\x7e';
}


balboa::ConfigRequest::ConfigRequest()
	: MessageBaseOutgoing(sizeof(*this), msConfigRequest)
{}


balboa::FilterConfigRequest::FilterConfigRequest()
	: MessageBaseOutgoing(sizeof(*this), msFilterConfigRequest),
	_payload{0x01, 0x00, 0x00}
{
}

balboa::ControlConfigRequest::ControlConfigRequest(
	bool isType1)
	: MessageBaseOutgoing(sizeof(*this), msControlConfigRequest)
{
	if (isType1)
	{
		_payload[0] = 0x02;
		_payload[1] = 0x00;
		_payload[2] = 0x00;
	}
	else
	{
		_payload[0] = 0x00;
		_payload[1] = 0x00;
		_payload[2] = 0x01;
	}
}


balboa::SetSpaTime::SetSpaTime(
	const balboa::SpaTime &time)
	: MessageBaseOutgoing(sizeof(*this), msSetTimeRequest),
	_hour(time.hour), _displayAs24Hr(time.displayAs24Hr), _minute(time.minute)
{}

balboa::ToggleItemMessage::ToggleItemMessage(
	ToggleItem item)
	: MessageBaseOutgoing(sizeof(*this), msToggleItemRequest),
	_item(item), _r(0)
{}


balboa::SetSpaTempMessage::SetSpaTempMessage(
	const balboa::SpaTemp &temp)
	: MessageBaseOutgoing(sizeof(*this), msSetTempRequest),
	_temp(temp.temp)
{}


balboa::SetSpaTempScaleMessage::SetSpaTempScaleMessage(
	bool scaleCelsius)
	: MessageBaseOutgoing(sizeof(*this), msSetTempScaleRequest),
	_scale(scaleCelsius)
{}

#endif