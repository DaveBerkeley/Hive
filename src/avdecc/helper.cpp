/*
* Copyright (C) 2017-2020, Emilien Vallot, Christophe Calmejane and other contributors

* This file is part of Hive.

* Hive is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* Hive is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.

* You should have received a copy of the GNU Lesser General Public License
* along with Hive.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "helper.hpp"

#include <hive/modelsLibrary/helper.hpp>
#include <hive/modelsLibrary/controllerManager.hpp>
#include <la/avdecc/utils.hpp>

#include <cctype>

namespace avdecc
{
namespace helper
{
QString protocolInterfaceTypeName(la::avdecc::protocol::ProtocolInterface::Type const& protocolInterfaceType)
{
	switch (protocolInterfaceType)
	{
		case la::avdecc::protocol::ProtocolInterface::Type::PCap:
			return "PCap";
		case la::avdecc::protocol::ProtocolInterface::Type::MacOSNative:
			return "MacOS Native";
		case la::avdecc::protocol::ProtocolInterface::Type::Proxy:
			return "Proxy";
		case la::avdecc::protocol::ProtocolInterface::Type::Virtual:
			return "Virtual";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return {};
	}
}

QString descriptorTypeToString(la::avdecc::entity::model::DescriptorType const& descriptorType) noexcept
{
	return QString::fromStdString(la::avdecc::entity::model::descriptorTypeToString(descriptorType));
}

QString acquireStateToString(la::avdecc::controller::model::AcquireState const& acquireState, la::avdecc::UniqueIdentifier const& owningController) noexcept
{
	switch (acquireState)
	{
		case la::avdecc::controller::model::AcquireState::Undefined:
			return "Undefined";
		case la::avdecc::controller::model::AcquireState::NotSupported:
			return "Not Supported";
		case la::avdecc::controller::model::AcquireState::NotAcquired:
			return "Not Acquired";
		case la::avdecc::controller::model::AcquireState::AcquireInProgress:
			return "Acquire In Progress";
		case la::avdecc::controller::model::AcquireState::Acquired:
			return "Acquired";
		case la::avdecc::controller::model::AcquireState::AcquiredByOther:
		{
			auto text = QString{ "Acquired by " };
			auto& controllerManager = hive::modelsLibrary::ControllerManager::getInstance();
			auto const& controllerEntity = controllerManager.getControlledEntity(owningController);
			if (controllerEntity)
			{
				text += hive::modelsLibrary::helper::smartEntityName(*controllerEntity);
			}
			else
			{
				text += hive::modelsLibrary::helper::uniqueIdentifierToString(owningController);
			}
			return text;
		}
		case la::avdecc::controller::model::AcquireState::ReleaseInProgress:
			return "Release In Progress";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return {};
	}
}

QString lockStateToString(la::avdecc::controller::model::LockState const& lockState, la::avdecc::UniqueIdentifier const& lockingController) noexcept
{
	switch (lockState)
	{
		case la::avdecc::controller::model::LockState::Undefined:
			return "Undefined";
		case la::avdecc::controller::model::LockState::NotSupported:
			return "Not Supported";
		case la::avdecc::controller::model::LockState::NotLocked:
			return "Not Locked";
		case la::avdecc::controller::model::LockState::LockInProgress:
			return "Lock In Progress";
		case la::avdecc::controller::model::LockState::Locked:
			return "Locked";
		case la::avdecc::controller::model::LockState::LockedByOther:
		{
			auto text = QString{ "Locked by " };
			auto& controllerManager = hive::modelsLibrary::ControllerManager::getInstance();
			auto const& controllerEntity = controllerManager.getControlledEntity(lockingController);
			if (controllerEntity)
			{
				text += hive::modelsLibrary::helper::smartEntityName(*controllerEntity);
			}
			else
			{
				text += hive::modelsLibrary::helper::uniqueIdentifierToString(lockingController);
			}
			return text;
		}
		case la::avdecc::controller::model::LockState::UnlockInProgress:
			return "Unlock In Progress";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return {};
	}
}

QString samplingRateToString(la::avdecc::entity::model::StreamFormatInfo::SamplingRate const& samplingRate) noexcept
{
	switch (samplingRate)
	{
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::Hz_500:
			return "500Hz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_8:
			return "8kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_16:
			return "16kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_24:
			return "24kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_32:
			return "32kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_44_1:
			return "44.1kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_48:
			return "48kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_88_2:
			return "88.2kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_96:
			return "96kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_176_4:
			return "176.4kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::kHz_192:
			return "192kHz";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::UserDefined:
			return "UserDefinedFreq";
		case la::avdecc::entity::model::StreamFormatInfo::SamplingRate::Unknown:
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return {};
	}
}

QString streamFormatToString(la::avdecc::entity::model::StreamFormatInfo const& format) noexcept
{
	QString fmtStr;

	auto const type = format.getType();
	switch (type)
	{
		case la::avdecc::entity::model::StreamFormatInfo::Type::None:
			fmtStr += "No format";
			break;
		case la::avdecc::entity::model::StreamFormatInfo::Type::IEC_61883_6:
		case la::avdecc::entity::model::StreamFormatInfo::Type::AAF:
		{
			if (type == la::avdecc::entity::model::StreamFormatInfo::Type::IEC_61883_6)
				fmtStr += "IEC 61883-6";
			else
				fmtStr += "AAF";
			fmtStr += ", " + samplingRateToString(format.getSamplingRate());
			fmtStr += ", ";
			switch (format.getSampleFormat())
			{
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::Int8:
					fmtStr += "PCM-INT-8";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::Int16:
					fmtStr += "PCM-INT-16";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::Int24:
					fmtStr += "PCM-INT-24";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::Int32:
					fmtStr += "PCM-INT-32";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::Int64:
					fmtStr += "PCM-INT-64";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::FixedPoint32:
					fmtStr += "PCM-FIXED-32";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::FloatingPoint32:
					fmtStr += "PCM-FLOAT-32";
					break;
				case la::avdecc::entity::model::StreamFormatInfo::SampleFormat::Unknown:
					fmtStr += "UnknownSize";
					break;
			}
			fmtStr += ", " + QString(format.isUpToChannelsCount() ? "up to " : "") + QString::number(format.getChannelsCount()) + " channels";
			fmtStr += QString(format.useSynchronousClock() ? "" : " (Async)");
			break;
		}
		case la::avdecc::entity::model::StreamFormatInfo::Type::ClockReference:
		{
			auto const& crfFormat = static_cast<la::avdecc::entity::model::StreamFormatInfoCRF const&>(format);
			fmtStr += "CRF";
			switch (crfFormat.getCRFType())
			{
				case la::avdecc::entity::model::StreamFormatInfoCRF::CRFType::User:
					fmtStr += " User";
					break;
				case la::avdecc::entity::model::StreamFormatInfoCRF::CRFType::AudioSample:
					fmtStr += " AudioSample";
					break;
				case la::avdecc::entity::model::StreamFormatInfoCRF::CRFType::MachineCycle:
					fmtStr += " MachineCycle";
					break;
				case la::avdecc::entity::model::StreamFormatInfoCRF::CRFType::Unknown:
					fmtStr += " UnknownType";
					break;
			}
			fmtStr += ", " + samplingRateToString(format.getSamplingRate());
			fmtStr += ", " + QString::number(crfFormat.getTimestampInterval()) + " intvl";
			fmtStr += ", " + QString::number(crfFormat.getTimestampsPerPdu()) + " ts/pdu";
			break;
		}
		default:
			fmtStr += "Unknown format type";
	}

	return fmtStr;
}

QString clockSourceToString(la::avdecc::controller::model::ClockSourceNode const& node) noexcept
{
	auto const* const descriptor = node.staticModel;

	return avdecc::helper::clockSourceTypeToString(descriptor->clockSourceType) + ", " + avdecc::helper::descriptorTypeToString(descriptor->clockSourceLocationType) + ":" + QString::number(descriptor->clockSourceLocationIndex);
}

inline void concatenateFlags(QString& flags, QString const& flag) noexcept
{
	if (!flags.isEmpty())
		flags += " | ";
	flags += flag;
}

QString flagsToString(la::avdecc::entity::AvbInterfaceFlags const flags) noexcept
{
	QString str;

	if (flags.empty())
		return "None";

	if (flags.test(la::avdecc::entity::AvbInterfaceFlag::GptpGrandmasterSupported))
		concatenateFlags(str, "GptpGrandmasterSupported");
	if (flags.test(la::avdecc::entity::AvbInterfaceFlag::GptpSupported))
		concatenateFlags(str, "GptpSupported");
	if (flags.test(la::avdecc::entity::AvbInterfaceFlag::SrpSupported))
		concatenateFlags(str, "SrpSupported");

	return str;
}

QString flagsToString(la::avdecc::entity::AvbInfoFlags const flags) noexcept
{
	QString str;

	if (flags.empty())
		return "None";

	if (flags.test(la::avdecc::entity::AvbInfoFlag::AsCapable))
		concatenateFlags(str, "AS Capable");
	if (flags.test(la::avdecc::entity::AvbInfoFlag::GptpEnabled))
		concatenateFlags(str, "Gptp Enabled");
	if (flags.test(la::avdecc::entity::AvbInfoFlag::SrpEnabled))
		concatenateFlags(str, "Srp Enabled");

	return str;
}

QString flagsToString(la::avdecc::entity::ClockSourceFlags const flags) noexcept
{
	QString str;

	if (flags.empty())
		return "None";

	if (flags.test(la::avdecc::entity::ClockSourceFlag::StreamID))
		concatenateFlags(str, "Stream");
	if (flags.test(la::avdecc::entity::ClockSourceFlag::LocalID))
		concatenateFlags(str, "Local");

	return str;
}

QString flagsToString(la::avdecc::entity::PortFlags const flags) noexcept
{
	QString str;

	if (flags.empty())
		return "None";

	if (flags.test(la::avdecc::entity::PortFlag::ClockSyncSource))
		concatenateFlags(str, "ClockSyncSource");
	if (flags.test(la::avdecc::entity::PortFlag::AsyncSampleRateConv))
		concatenateFlags(str, "AsyncSampleRateConv");
	if (flags.test(la::avdecc::entity::PortFlag::SyncSampleRateConv))
		concatenateFlags(str, "SyncSampleRateConv");

	return str;
}

QString flagsToString(la::avdecc::entity::StreamInfoFlags const flags) noexcept
{
	QString str;

	if (flags.test(la::avdecc::entity::StreamInfoFlag::ClassB))
		concatenateFlags(str, "ClassB");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::FastConnect))
		concatenateFlags(str, "FastConnect");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::SavedState))
		concatenateFlags(str, "SavedState");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::StreamingWait))
		concatenateFlags(str, "StreamingWait");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::SupportsEncrypted))
		concatenateFlags(str, "SupportsEncrypted");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::EncryptedPdu))
		concatenateFlags(str, "EncryptedPdu");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::TalkerFailed))
		concatenateFlags(str, "TalkerFailed");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::StreamVlanIDValid))
		concatenateFlags(str, "StreamVlanIDValid");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::Connected))
		concatenateFlags(str, "Connected");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::MsrpFailureValid))
		concatenateFlags(str, "MsrpFailureValid");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::StreamDestMacValid))
		concatenateFlags(str, "StreamDestMacValid");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::MsrpAccLatValid))
		concatenateFlags(str, "MsrpAccLatValid");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::StreamIDValid))
		concatenateFlags(str, "StreamIDValid");
	if (flags.test(la::avdecc::entity::StreamInfoFlag::StreamFormatValid))
		concatenateFlags(str, "StreamFormatValid");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString flagsToString(la::avdecc::entity::StreamInfoFlagsEx const flags) noexcept
{
	QString str;

	if (flags.test(la::avdecc::entity::StreamInfoFlagEx::Registering))
		concatenateFlags(str, "Registering");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString flagsToString(la::avdecc::entity::MilanInfoFeaturesFlags const flags) noexcept
{
	QString str;

	if (flags.test(la::avdecc::entity::MilanInfoFeaturesFlag::Redundancy))
		concatenateFlags(str, "Redundancy");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString probingStatusToString(la::avdecc::entity::model::ProbingStatus const status) noexcept
{
	switch (status)
	{
		case la::avdecc::entity::model::ProbingStatus::Disabled:
			return "Disabled";
		case la::avdecc::entity::model::ProbingStatus::Passive:
			return "Passive";
		case la::avdecc::entity::model::ProbingStatus::Active:
			return "Active";
		case la::avdecc::entity::model::ProbingStatus::Completed:
			return "Completed";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return "Unknown";
	}
}

QString capabilitiesToString(la::avdecc::entity::EntityCapabilities const caps) noexcept
{
	QString str;

	if (caps.test(la::avdecc::entity::EntityCapability::EfuMode))
		concatenateFlags(str, "EfuMode");
	if (caps.test(la::avdecc::entity::EntityCapability::AddressAccessSupported))
		concatenateFlags(str, "AddressAccessSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::GatewayEntity))
		concatenateFlags(str, "GatewayEntity");
	if (caps.test(la::avdecc::entity::EntityCapability::AemSupported))
		concatenateFlags(str, "AemSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::LegacyAvc))
		concatenateFlags(str, "LegacyAvc");
	if (caps.test(la::avdecc::entity::EntityCapability::AssociationIDSupported))
		concatenateFlags(str, "AssociationIDSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::VendorUniqueSupported))
		concatenateFlags(str, "VendorUniqueSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::ClassASupported))
		concatenateFlags(str, "ClassASupported");
	if (caps.test(la::avdecc::entity::EntityCapability::ClassBSupported))
		concatenateFlags(str, "ClassBSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::GptpSupported))
		concatenateFlags(str, "GptpSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::AemAuthenticationSupported))
		concatenateFlags(str, "AemAuthenticationSupported");
	if (caps.test(la::avdecc::entity::EntityCapability::AemAuthenticationRequired))
		concatenateFlags(str, "AemAuthenticationRequired");
	if (caps.test(la::avdecc::entity::EntityCapability::AemPersistentAcquireSupported))
		concatenateFlags(str, "AemPersistentAcquireSupported");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString capabilitiesToString(la::avdecc::entity::TalkerCapabilities const caps) noexcept
{
	QString str;

	if (caps.test(la::avdecc::entity::TalkerCapability::Implemented))
		concatenateFlags(str, "Implemented");
	if (caps.test(la::avdecc::entity::TalkerCapability::OtherSource))
		concatenateFlags(str, "OtherSource");
	if (caps.test(la::avdecc::entity::TalkerCapability::ControlSource))
		concatenateFlags(str, "ControlSource");
	if (caps.test(la::avdecc::entity::TalkerCapability::MediaClockSource))
		concatenateFlags(str, "MediaClockSource");
	if (caps.test(la::avdecc::entity::TalkerCapability::SmpteSource))
		concatenateFlags(str, "SmpteSource");
	if (caps.test(la::avdecc::entity::TalkerCapability::MidiSource))
		concatenateFlags(str, "MidiSource");
	if (caps.test(la::avdecc::entity::TalkerCapability::AudioSource))
		concatenateFlags(str, "AudioSource");
	if (caps.test(la::avdecc::entity::TalkerCapability::VideoSource))
		concatenateFlags(str, "VideoSource");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString capabilitiesToString(la::avdecc::entity::ListenerCapabilities const caps) noexcept
{
	QString str;

	if (caps.test(la::avdecc::entity::ListenerCapability::Implemented))
		concatenateFlags(str, "Implemented");
	if (caps.test(la::avdecc::entity::ListenerCapability::OtherSink))
		concatenateFlags(str, "OtherSink");
	if (caps.test(la::avdecc::entity::ListenerCapability::ControlSink))
		concatenateFlags(str, "ControlSink");
	if (caps.test(la::avdecc::entity::ListenerCapability::MediaClockSink))
		concatenateFlags(str, "MediaClockSink");
	if (caps.test(la::avdecc::entity::ListenerCapability::SmpteSink))
		concatenateFlags(str, "SmpteSink");
	if (caps.test(la::avdecc::entity::ListenerCapability::MidiSink))
		concatenateFlags(str, "MidiSink");
	if (caps.test(la::avdecc::entity::ListenerCapability::AudioSink))
		concatenateFlags(str, "AudioSink");
	if (caps.test(la::avdecc::entity::ListenerCapability::VideoSink))
		concatenateFlags(str, "VideoSink");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString capabilitiesToString(la::avdecc::entity::ControllerCapabilities const caps) noexcept
{
	QString str;

	if (caps.test(la::avdecc::entity::ControllerCapability::Implemented))
		concatenateFlags(str, "Implemented");

	if (str.isEmpty())
		str = "None";
	return str;
}

QString clockSourceTypeToString(la::avdecc::entity::model::ClockSourceType const type) noexcept
{
	switch (type)
	{
		case la::avdecc::entity::model::ClockSourceType::Internal:
			return "Internal";
		case la::avdecc::entity::model::ClockSourceType::External:
			return "External";
		case la::avdecc::entity::model::ClockSourceType::InputStream:
			return "Input Stream";
		case la::avdecc::entity::model::ClockSourceType::Expansion:
			return "Expansion";
		default:
			AVDECC_ASSERT(false, "Not handled!");
	}
	return "Unknown";
}

QString audioClusterFormatToString(la::avdecc::entity::model::AudioClusterFormat const format) noexcept
{
	switch (format)
	{
		case la::avdecc::entity::model::AudioClusterFormat::Iec60958:
			return "IEC 60958";
		case la::avdecc::entity::model::AudioClusterFormat::Mbla:
			return "MBLA";
		case la::avdecc::entity::model::AudioClusterFormat::Midi:
			return "MIDI";
		case la::avdecc::entity::model::AudioClusterFormat::Smpte:
			return "SMPTE";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return "Unknown";
	}
}

QString memoryObjectTypeToString(la::avdecc::entity::model::MemoryObjectType const type) noexcept
{
	switch (type)
	{
		case la::avdecc::entity::model::MemoryObjectType::FirmwareImage:
			return "Firmware Image";
		case la::avdecc::entity::model::MemoryObjectType::VendorSpecific:
			return "Vendor Specific";
		case la::avdecc::entity::model::MemoryObjectType::CrashDump:
			return "Crash Dump";
		case la::avdecc::entity::model::MemoryObjectType::LogObject:
			return "Log Object";
		case la::avdecc::entity::model::MemoryObjectType::AutostartSettings:
			return "Autostart Settings";
		case la::avdecc::entity::model::MemoryObjectType::SnapshotSettings:
			return "Snapshot Settings";
		case la::avdecc::entity::model::MemoryObjectType::SvgManufacturer:
			return "Svg Manufacturer";
		case la::avdecc::entity::model::MemoryObjectType::SvgEntity:
			return "Svg Entity";
		case la::avdecc::entity::model::MemoryObjectType::SvgGeneric:
			return "Svg Generic";
		case la::avdecc::entity::model::MemoryObjectType::PngManufacturer:
			return "Png Manufacturer";
		case la::avdecc::entity::model::MemoryObjectType::PngEntity:
			return "Png Entity";
		case la::avdecc::entity::model::MemoryObjectType::PngGeneric:
			return "Png Generic";
		case la::avdecc::entity::model::MemoryObjectType::DaeManufacturer:
			return "Dae Manufacturer";
		case la::avdecc::entity::model::MemoryObjectType::DaeEntity:
			return "Dae Entity";
		case la::avdecc::entity::model::MemoryObjectType::DaeGeneric:
			return "Dae Generic";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return "Unknown";
	}
}

QString certificationVersionToString(std::uint32_t const certificationVersion) noexcept
{
	return QString("%1.%2.%3.%4").arg(certificationVersion >> 24 & 0xFF).arg(certificationVersion >> 16 & 0xFF).arg(certificationVersion >> 8 & 0xFF).arg(certificationVersion & 0xFF);
}

QString loggerLayerToString(la::avdecc::logger::Layer const layer) noexcept
{
	switch (layer)
	{
		case la::avdecc::logger::Layer::Generic:
			return "Generic";
		case la::avdecc::logger::Layer::Serialization:
			return "Serialization";
		case la::avdecc::logger::Layer::ProtocolInterface:
			return "Protocol Interface";
		case la::avdecc::logger::Layer::AemPayload:
			return "AemPayload";
		case la::avdecc::logger::Layer::Entity:
			return "Entity";
		case la::avdecc::logger::Layer::ControllerEntity:
			return "Controller Entity";
		case la::avdecc::logger::Layer::ControllerStateMachine:
			return "Controller State Machine";
		case la::avdecc::logger::Layer::Controller:
			return "Controller";
		case la::avdecc::logger::Layer::JsonSerializer:
			return "Json Serializer";
		case la::avdecc::logger::Layer::FirstUserLayer:
			return "Hive";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return "Unknown";
	}
}

QString loggerLevelToString(la::avdecc::logger::Level const& level) noexcept
{
	switch (level)
	{
		case la::avdecc::logger::Level::Trace:
			return "Trace";
		case la::avdecc::logger::Level::Debug:
			return "Debug";
		case la::avdecc::logger::Level::Info:
			return "Info";
		case la::avdecc::logger::Level::Warn:
			return "Warning";
		case la::avdecc::logger::Level::Error:
			return "Error";
		case la::avdecc::logger::Level::None:
			return "None";
		default:
			AVDECC_ASSERT(false, "Not handled!");
			return "Unknown";
	}
}

} // namespace helper
} // namespace avdecc
