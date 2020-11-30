/*
 * ActiveLoggerImpl.hpp
 *
 *  Created on: Mar 28, 2014
 *      Author: tcanham
 */

#ifndef ACTIVELOGGERIMPL_HPP_
#define ACTIVELOGGERIMPL_HPP_

#include <Svc/ActiveLogger/ActiveLoggerComponentAc.hpp>
#include <Fw/Log/LogPacket.hpp>
#include <ActiveLoggerImplCfg.hpp>

namespace Svc {

    class ActiveLoggerImpl: public ActiveLoggerComponentBase {
        public:
            ActiveLoggerImpl(const char* compName); //!< constructor
            virtual ~ActiveLoggerImpl(); //!< destructor
            void init(
                    NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
                    NATIVE_INT_TYPE instance /*!< The instance number*/
                    ); //!< initialization function
        PROTECTED:
        PRIVATE:
            void LogRecv_handler(NATIVE_INT_TYPE portNum, FwEventIdType id, Fw::Time &timeTag, Fw::LogSeverity severity, Fw::LogBuffer &args);
            void loqQueue_internalInterfaceHandler(FwEventIdType id, Fw::Time &timeTag, QueueLogSeverity severity, Fw::LogBuffer &args);

            void ALOG_SET_EVENT_REPORT_FILTER_cmdHandler(
                    FwOpcodeType opCode,
                    U32 cmdSeq,
                    InputFilterLevel FilterLevel,
                    InputFilterEnabled FilterEnable);

            void ALOG_SET_EVENT_SEND_FILTER_cmdHandler(
                    FwOpcodeType opCode,
                    U32 cmdSeq,
                    SendFilterLevel FilterLevel,
                    SendFilterEnabled FilterEnable);

            void ALOG_SET_ID_FILTER_cmdHandler(
                    FwOpcodeType opCode, //!< The opcode
                    U32 cmdSeq, //!< The command sequence number
                    U32 ID,
                    IdFilterEnabled IdFilterEnable //!< ID filter state
                );

            void ALOG_DUMP_FILTER_STATE_cmdHandler(
                    FwOpcodeType opCode, //!< The opcode
                    U32 cmdSeq //!< The command sequence number
                );

            //! Handler implementation for pingIn
            //!
            void pingIn_handler(
                const NATIVE_INT_TYPE portNum, /*!< The port number*/
                U32 key /*!< Value to return to pinger*/
            );

            // Input filter state
            struct t_inputFilterState {
                InputFilterEnabled enabled; //<! filter is enabled
            } m_inFilterState[InputFilterLevel_MAX];

            // Send filter state
            struct t_sendFilterState {
                SendFilterEnabled enabled; //!< filter is enabled
            } m_sendFilterState[SendFilterLevel_MAX];

            // Working members
            Fw::LogPacket m_logPacket; //!< packet buffer for assembling log packets
            Fw::ComBuffer m_comBuffer; //!< com buffer for sending event buffers

            // array of filtered event IDs.
            // value of 0 means no entry
            FwEventIdType m_filteredIDs[TELEM_ID_FILTER_SIZE];

    };

}
#endif /* ACTIVELOGGERIMPL_HPP_ */
