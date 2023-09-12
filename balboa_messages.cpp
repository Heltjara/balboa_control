#include "balboa_messages.hpp"

using namespace balboa;

void SettingsRequest::SetSettingsType(request_type type, data_type &data)
{
    data.payload[0] = 0x00;
    data.payload[1] = 0x00;
    data.payload[2] = 0x00;

    switch (type)
    {
    case PANEL_REQUEST:
        data.payload[2] = 0x01;
        break;

    case FILTER_CYCLES_REQUEST:
        data.payload[0] = 0x01;
        break;

    case INFORMATION_REQUEST:
        /**
         * Sent when the app goes to the Controls screen,
         * then it gets a response, then sends a Panel Request.
         */
        data.payload[0] = 0x02;
        break;

    case PREFERENCES_REQUEST:
        data.payload[0] = 0x08;
        break;

    case FAULT_LOG_REQUEST:
        data.payload[0] = 0x20;
        /**
         * byte 1 :
         * 0x00 - first entry
         * ** - Values larger than count roll-over (modulo)
         * 0xff - last entry
         */
        break;
    default:
        break;
    }
}

void ToggleItemRequest::Toggle(ToggleItemRequest::ToggleItem item,
                               data_type &data)
{
    data.item = item;
    data.unknown = 0;
}

void SetTempRequest::SetTemperature(SpaTemp &temp, data_type &data)
{
    data.temperature = temp.temperature;
}

void SetTimeRequest::SetTime(SpaTime &time, data_type &data)
{
    data.hour = time.hour;
    data.time_format = time.display_as_24hr;
    data.minute = time.minute;
}

void FilterConfigRequest::SetFilterConfig(data_type &data)
{
    data.filter = 0x01;
    data.unknown1 = 0;
    data.unknown2 = 0;
}

void SetTempScaleRequest::SetScale(bool isCelsius, data_type &data)
{
    data.scale = isCelsius;
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