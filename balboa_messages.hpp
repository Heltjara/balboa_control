#pragma once
#include <cstddef>
#include <cstdint>

/**
 * The file in the most part is taken from:
 * https://github.com/MHotchin/BalBoaSpa
 *
 */
/**
* Message definitions for talking to BalBoa spas over Wifi.  Most of this info was taken
* from https://github.com/ccutrer/balboa_worldwide_app
**/
namespace balboa
{
    template <uint8_t A, uint8_t B, uint8_t C>
    struct MT_struct
    {
        static const uint8_t byte1 = A;
        static const uint8_t byte2 = B;
        static const uint8_t byte3 = C;
    };

/*****************************************************************
*************************REQUESTS*********************************
******************************************************************/

    class ConfigRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x04> header_type;

        struct data_type
        {
            
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class ToggleItemRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x11> header_type;

        struct data_type
        {
            uint8_t item;
            uint8_t unknown;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        enum ToggleItem
        {
            PUMP1      = 0x04,
            PUMP2      = 0x05,
            LIGHTS     = 0x11,
            TEMP_RANGE = 0x50
        };

        static void Toggle(ToggleItem item, data_type &data);
    };

    class SetTempRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x20> header_type;

        struct data_type
        {
            uint8_t temperature;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        struct SpaTemp
        {
            uint8_t temperature;
            bool is_celsius;
        };

        static void SetTemperature(SpaTemp &temp, data_type &data);
    };

    class SetTimeRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x21> header_type;

        struct data_type
        {
            uint8_t hour : 7;
            uint8_t time_format : 1; // true if 24h format
            uint8_t minute;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        struct SpaTime
        {
            uint8_t hour;
            uint8_t minute;
            bool display_as_24hr;
        };

        static void SetTime(SpaTime &time, data_type &data);
    };

    class FilterConfigRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x22> header_type;

        struct data_type
        {
            uint8_t filter;  // TODO: not sure, should be 0x01, filter number?
            uint8_t unknown1;
            uint8_t unknown2;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        static void SetFilterConfig(data_type &data);
    };

    class SettingsRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x22> header_type;

        struct data_type
        {
            uint8_t payload[3];
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        enum request_type
        {
            PANEL_REQUEST,
            FILTER_CYCLES_REQUEST,
            INFORMATION_REQUEST,
            PREFERENCES_REQUEST,
            FAULT_LOG_REQUEST
        };

        static void SetSettingsType(request_type type, data_type &data);
    };

    class SetFilterConfigRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x23> header_type;

        struct data_type
        {
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class SetTempScaleRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x27> header_type;

        struct data_type
        {
            static const uint8_t unknown = 0x01;
            uint8_t scale;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        static void SetScale(bool isCelsius, data_type &data);
    };

    class SetWiFiSettingsRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x92> header_type;

        struct data_type
        {
            uint8_t config_type;
            uint8_t sid_length;
            uint8_t ssid[32];
            uint8_t enc_type;
            uint8_t pass_length;
            uint8_t passkey[64];
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

/*****************************************************************
**************************RESPONSES*******************************
******************************************************************/
    class ReadyToSend
    {
    public:
        typedef MT_struct<0x10, 0xBF, 0x06> header_type;

        struct data_type
        {
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class Status
    {
    public:
        typedef MT_struct<0xFF, 0xAF, 0x13> header_type;

        struct data_type
        {
            uint8_t hold_mode;             // 00, hold mode == 0x05
            uint8_t priming;               // 01, priming == 0x01
            uint8_t current_temp;          // 02, diveide by 2 if C, 0xFF == unknown
            uint8_t hour;                  // 03
            uint8_t minute;                // 04
            uint8_t heating_mode;          // 05, 0 - ready, 1 - rest, 3 - ready in rest
            uint8_t panel_message;         // 06. 4 first bits?
            uint8_t unknown1;              // 07, 
            uint8_t hold_time;             // 08  if system_hold is true
            uint8_t celsius : 1;           // 09  true if temperature in celsius
            uint8_t time_format : 1;       // 09 true if 24h format
            uint8_t filter1_running : 1;   // 09
            uint8_t filter2_running : 1;   // 09
            uint8_t : 0;                   // 09 pad
            uint8_t unknown2 : 2;          // 10 pad ?
            uint8_t temp_range : 1;        // 10 temperature range: 0 = low, 1 = high
            uint8_t unknown3 : 1;          // 10 pad ?
            uint8_t heating : 2;           // 10 heating state?
            uint8_t : 0;                   // 10 pad
            uint8_t pump1 : 2;             // 11 pump 1 status
            uint8_t pump2 : 2;             // 11 pump 2 status
            uint8_t pump3 : 2;             // 11 pump 3 status
            uint8_t : 0;                   // 11 pad
            uint8_t unknown4;              // 12
            uint8_t unknown5 : 1;          // 13 pad ?
            uint8_t circulation_pump : 1;  // 13
            uint8_t blower : 2;            // 13 ?
            uint8_t : 0;                   // 13 pad
            uint8_t lights : 2;            // 14 0b11 == lights on?
            uint8_t : 0;                   // 14 pad
            uint8_t mister : 1;            // 15 
            uint8_t : 0;                   // 15 pad
            uint8_t unknown6;              // 16
            uint8_t unknown7;              // 17
            uint8_t unknown8 : 1;          // 18 both 18 & 19, bit 2 seem related to time not
            uint8_t time_unset : 1;        // 18 yet set.
            uint8_t : 0;                   // 18 pad
            uint8_t unknown8 : 1;          // 19 both 18 & 19, bit 2 seem related to time not
            uint8_t time_unset : 1;        // 19 yet set.
            uint8_t : 0;                   // 19 pad
            uint8_t set_temp;              // 20
            uint8_t unknown9 : 2;          // 21
            uint8_t system_hold : 1;       // 21 see hold_mode, byte 1
            uint8_t : 0;                   // 21 pad
            uint8_t unknown10;             // 22
            uint8_t unknown11;             // 23
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class FilterCyclesResponse
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x23> header_type;

        struct data_type
        {
            uint8_t filter1_start_hour;       // 00
            uint8_t filter1_start_minute;     // 01
            uint8_t filter1_duration_hours;   // 02
            uint8_t filter1_duration_minutes; // 03
            uint8_t filter2_start_hour : 7;   // 04
            uint8_t filter2_enabled : 1;      // 04
            uint8_t filter2_start_minute;     // 05
            uint8_t filter2_duration_hours;   // 06
            uint8_t filter2_duration_minutes; // 07
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class InformationResponse
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x24> header_type;

        struct data_type
        {
            uint8_t software_id[2];       // 00, 01
            uint8_t software_version[2];  // 02, 03
            uint8_t system_model[8];      // 04->11
            uint8_t currentSetup;         // 12
            uint32_t signature;           // 13->16
            uint16_t heater_type;         // 17, 18 : 0x0a - standard
            uint16_t dip_switch_settings; // 19, 20
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class FaultLogResponse
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x28> header_type;

        struct data_type
        {
            uint8_t fault_count;
            uint8_t entry_number;
            uint8_t message_code;
            uint8_t days_ago;
            uint8_t hours;
            uint8_t minutes;
            uint8_t flags; //TODO: bitfield? heating mode, temp range
            uint8_t set_temperature;
            uint8_t sensor_a_temp;
            uint8_t sensor_b_temp;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class ControlConfig2Response
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x2e> header_type;

        struct data_type
        {
            uint8_t unknown[6];
            // TODO: Unknown
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class ConfigResponse
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x94> header_type;

        struct data_type
        {
            uint8_t unknown[25];
            // TODO: Unknown
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class SetTempRange 
    {
    public:
        typedef MT_struct<0xFF, 0xAF, 0x26> header_type;

        struct data_type
        {
            uint8_t unknown[24];
            // TODO: finish
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };



    template <class MS>
    struct Message
    {
        static const uint8_t prefix = 0x7e;
        typename MS::length_type length;
        typename MS::header_type type;
        typename MS::data_type data;
        uint8_t crc;
        static const uint8_t suffix = 0x7e;

        Message(){};

        void Dump() const;
        void SetCRC();
        bool CheckCRC() const;
        uint8_t CalcCRC() const;
    };

#if 0
    constexpr uint32_t MESSAGE_ID(uint8_t b1, uint8_t b2, uint8_t b3)
    {
        return ((((uint32_t)b1) | (((uint32_t)b2) << 8) | (((uint32_t)b3) << 16)) & 0x00FFFFFF);
    }

    //  Message IDs for responses from the hot-tub.
    enum SpaResponseMessageID : uint32_t
    {
        msReadyToSend = MESSAGE_ID(0x10, 0xbf, 0x06),

        msStatus = MESSAGE_ID(0xff, 0xaf, 0x13),
        msSetTempRange = MESSAGE_ID(0xff, 0xaf, 0x26),

        msFilterConfigResponse = MESSAGE_ID(0x0a, 0xbf, 0x23),
        msControlConfigResponse = MESSAGE_ID(0x0a, 0xbf, 0x24),
        msFaultLogResponse = MESSAGE_ID(0x0a, 0xbf, 0x28),
        msControlConfig2Response = MESSAGE_ID(0x0a, 0xbf, 0x2e),
        msConfigResponse = MESSAGE_ID(0x0a, 0xbf, 0x94),
    };

    //  Message Id's for commands send to the hot-tub
    enum SpaCommandMessageID : uint32_t
    {
        msConfigRequest = MESSAGE_ID(0x0a, 0xbf, 0x04),
        msToggleItemRequest = MESSAGE_ID(0x0a, 0xbf, 0x11),
        msSetTempRequest = MESSAGE_ID(0x0a, 0xbf, 0x20),
        msSetTimeRequest = MESSAGE_ID(0x0a, 0xbf, 0x21),
        msFilterConfigRequest = MESSAGE_ID(0x0a, 0xbf, 0x22), // Used after msConfigRequest
        msControlConfigRequest = MESSAGE_ID(0x0a, 0xbf, 0x22),
        msSetFilterConfigRequest = MESSAGE_ID(0x0a, 0xbf, 0x23),
        msSetTempScaleRequest = MESSAGE_ID(0x0a, 0xbf, 0x27),
        msSetWiFiSettingsRequest = MESSAGE_ID(0x0a, 0xbf, 0x92),
    };
    //  Each message consists of a payload and 7 bytes overhead.  At the beginning of each
    //  message is a prefix (always 0x7e), then length of the message *without the prefix
    //  or suffix*, and a three byte message ID.
    struct MessageBase
    {
        uint8_t _prefix;
        uint8_t _length;
        uint32_t _messageType : 24;

        void Dump() const;
        void Dump(size_t) const;
        void SetCRC();
        bool CheckCRC() const;
        uint8_t CalcCRC() const;

    protected:
        MessageBase(size_t, unsigned long);
        MessageBase() = default;
    } __attribute__((packed));

    //  The last two bytes of overhead are a check byte (8 bit CRC), and a suffix (also
    //  always 0x7e).
    struct MessageSuffix
    {
        uint8_t _check;
        uint8_t _suffix;

        MessageSuffix();
    } __attribute__((packed));


    //  Some type safety, make sure the right message ID's are applied to the right
    //  messages.
    struct MessageBaseIncoming : public MessageBase
    {
    };

    struct MessageBaseOutgoing : public MessageBase
    {
    protected:
        MessageBaseOutgoing(size_t size, SpaCommandMessageID id) 
            : MessageBase(size, id)
        {};
    };



    //  Following messages are only received.  They are never instantiated, hence no
    //  constructor.  
    //
    //  Using bitfields, we can read the message directly from memory without any
    //  bit-twiddling.
    //
    //  As needed, unknown areas are marked as '_r*'.  Note that some bitfields are
    //  skipped rather than marked.

    struct ConfigResponseMessage : public MessageBaseIncoming
    {
        uint8_t _r[25];    //  Unknown structure
        MessageSuffix _suffix;
    } __attribute__((packed));

    struct StatusMessage : public MessageBaseIncoming
    {                               // byte #
        uint8_t _r1;                   // 00
        uint8_t _priming : 1;          // 01
        uint8_t : 0;                   //
        uint8_t _currentTemp;          // 02
        uint8_t _hour;                 // 03
        uint8_t _minute;               // 04
        uint8_t _heatingMode : 2;      // 05
        uint8_t : 0;                   // 
        uint8_t _panelMessage : 4;     // 06
        uint8_t : 0;                   //
        uint8_t _r2;                   // 07, 
        uint8_t _holdTime;             // 08  if _systemHold is true
        uint8_t _tempScaleCelsius : 1; // 09
        uint8_t _24hrTime : 1;         //
        uint8_t _filter1Running : 1;   // 
        uint8_t _filter2Running : 1;   //
        uint8_t : 0;                   //
        uint8_t _r3 : 2;               // 10
        uint8_t _tempRange : 1;        //
        uint8_t _r4 : 1;               //
        uint8_t _heating : 2;          //
        uint8_t : 0;                   //
        uint8_t _pump1 : 2;            // 11
        uint8_t _pump2 : 2;            //
        uint8_t : 0;                   //
        uint8_t _r5;                   // 12
        uint8_t _r6 : 1;               // 13
        uint8_t _circPump : 1;         //
        uint8_t : 0;                   //
        uint8_t _light : 2;            // 14
        uint8_t : 0;                   //
        uint8_t _r7[3];                // 15->17
        uint8_t _r7a : 1;              // both 18 & 19, bit 2 seem related to time not
        uint8_t _timeUnset : 1;        // yet set.
        uint8_t : 0;
        uint8_t _r7b;                  // 19
        uint8_t _setTemp;              // 20
        uint8_t _r8 : 2;               // 21
        uint8_t _systemHold : 1;
        uint8_t : 0;
        uint8_t _r9[2];                // 22, 23

        MessageSuffix _suffix;      

    } __attribute__((packed));

    struct FilterStatusMessage :public MessageBaseIncoming
    {                                // byte
        uint8_t filter1StartHour;       // 00
        uint8_t filter1StartMinute;     // 01
        uint8_t filter1DurationHours;   // 02
        uint8_t filter1DurationMinutes; // 03
        uint8_t filter2StartHour : 7;   // 04
        uint8_t filter2enabled : 1;     //
        uint8_t filter2StartMinute;     // 05
        uint8_t filter2DurationHours;   // 06
        uint8_t filter2DurationMinutes; // 07

        MessageSuffix _suffix;       
    } __attribute__((packed));


    struct ControlConfigResponse : public MessageBaseIncoming
    {                        // byte
        uint8_t _version[3];    // 00, 01, 02
        uint8_t _r1;            // 03
        uint8_t _name[8];       // 04->11
        uint8_t _currentSetup;  // 12
        uint32_t _signature; // 13->16
        uint8_t _r2[4];         // 17->20

        MessageSuffix _sufffix;
    } __attribute__((packed));


    struct ControlConfig2Response : public MessageBaseIncoming
    {
        uint8_t _r1[6];

        MessageSuffix _suffix;
    };

    //  Following messages are only sent.  Once contructed, they are ready to go.
    struct ConfigRequest : public MessageBaseOutgoing
    {
        ConfigRequest();
        //  No content
        MessageSuffix _suffix;
    } __attribute__((packed));

    struct FilterConfigRequest : public MessageBaseOutgoing
    {
        FilterConfigRequest();

        uint8_t _payload[3];

        MessageSuffix _suffix;
    } __attribute__((packed));

    struct ControlConfigRequest : public MessageBaseOutgoing
    {
        ControlConfigRequest(bool type1);

        uint8_t _payload[3];

        MessageSuffix _suffix;
    }  __attribute__((packed));

    struct SetSpaTime : public MessageBaseOutgoing
    {
        SetSpaTime(const SpaTime &);

        uint8_t _hour : 7;
        uint8_t _displayAs24Hr : 1;
        uint8_t _minute;

        MessageSuffix _suffix;
    } __attribute__((packed));


    enum ToggleItem
    {
        tiLights = 0x11,
        tiPump1 = 0x04,
        tiPump2 = 0x05,
        tiTempRange = 0x50
    };

    struct ToggleItemMessage : public MessageBaseOutgoing
    {
        ToggleItemMessage(ToggleItem Item);

        uint8_t _item;
        uint8_t _r;

        MessageSuffix _suffix;
    } __attribute__((packed));

    struct SetSpaTempMessage : public MessageBaseOutgoing
    {
        SetSpaTempMessage(const SpaTemp &);

        uint8_t _temp;

        MessageSuffix _suffix;
    } __attribute__((packed));

    struct SetSpaTempScaleMessage : public MessageBaseOutgoing
    {
        SetSpaTempScaleMessage(bool scaleCelsius);

        uint8_t _r1 = 0x01;
        uint8_t _scale;

        MessageSuffix _suffix;
    } __attribute__((packed));

#endif

};
