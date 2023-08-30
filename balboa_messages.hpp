#pragma once
#include <cstddef>
#include <cstdint>

/**
 * The file in the most part is taken from:
 * https://github.com/MHotchin/BalBoaSpa
 *
 */

namespace balboa
{

    //  Message definitions for talking to BalBoa spas over Wifi.  Most of this info was taken
    //  from https://github.com/ccutrer/balboa_worldwide_app

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

    template <uint8_t A, uint8_t B, uint8_t C>
    struct MT_struct
    {
        static const uint8_t byte1 = A;
        static const uint8_t byte2 = B;
        static const uint8_t byte3 = C;
    };

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
            uint8_t _item;
            uint8_t _r;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        enum ToggleItem
        {
            tiLights = 0x11,
            tiPump1 = 0x04,
            tiPump2 = 0x05,
            tiTempRange = 0x50
        };

        static void Toggle(ToggleItem item, data_type &data);
    };

    class SetTempRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x20> header_type;

        struct data_type
        {
            uint8_t _temp;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        struct SpaTemp
        {
            uint8_t temp;
            bool isCelsiusX2;
        };

        static void SetTemperature(SpaTemp &temp, data_type &data);
    };

    class SetTimeRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x21> header_type;

        struct data_type
        {
            uint8_t _hour : 7;
            uint8_t _displayAs24Hr : 1;
            uint8_t _minute;
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        struct SpaTime
        {
            uint8_t hour;
            uint8_t minute;
            bool displayAs24Hr;
        };

        static void SetTime(SpaTime &time, data_type &data);
    };

    class FilterConfigRequest
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x22> header_type;

        struct data_type
        {
            uint8_t _payload[3];
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };

        static void SetPayload(data_type &data);
    };

    class ControlConfigRequest
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

        static void SetPayload(bool isType1, data_type &data);
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
            static const uint8_t _r1 = 0x01;
            uint8_t _scale;
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
            uint8_t _configType;
            uint8_t _sid_length;
            uint8_t _ssid[32];
            uint8_t _enc_type;
            uint8_t _pass_length;
            uint8_t _passkey[64];
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

        
    class FilterConfigResponse
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x23> header_type;

        struct data_type
        {
            uint8_t filter1StartHour;       // 00
            uint8_t filter1StartMinute;     // 01
            uint8_t filter1DurationHours;   // 02
            uint8_t filter1DurationMinutes; // 03
            uint8_t filter2StartHour : 7;   // 04
            uint8_t filter2enabled : 1;     //
            uint8_t filter2StartMinute;     // 05
            uint8_t filter2DurationHours;   // 06
            uint8_t filter2DurationMinutes; // 07
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

    class ControlConfigResponse
    {
    public:
        typedef MT_struct<0x0A, 0xBF, 0x24> header_type;

        struct data_type
        {
            uint8_t _r[25];
            //TODO: finish
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
            uint8_t _r[10];
            // TODO: finish
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
            uint8_t _r[6];
            // TODO: finish
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
            uint8_t _r[25];
            // TODO: finish
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
            uint8_t _r[24];
            // TODO: finish
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
            uint8_t _r[24];
            // TODO: finish
        };

        struct length_type
        {
            static constexpr uint8_t length = sizeof(data_type);
        };
    };

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

    template <class MS>
    struct Message
    {
        static const uint8_t _prefix = 0x7e;
        typename MS::length_type _length;
        typename MS::header_type _type;
        typename MS::data_type _data;
        uint8_t _crc;
        static const uint8_t _suffix = 0x7e;

        Message(){};

        void Dump() const;
        void SetCRC();
        bool CheckCRC() const;
        uint8_t CalcCRC() const;
    };

#if 0
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
