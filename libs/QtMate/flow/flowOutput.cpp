#include "QtMate/flow/flowOutput.hpp"
#include "QtMate/flow/flowConnection.hpp"
#include "QtMate/flow/flowStyle.hpp"

#include <QPainter>

namespace qtMate::flow
{
FlowOutput::~FlowOutput()
{
	for (auto* connection : _connections)
	{
		connection->setOutput(nullptr);
	}
	_connections.clear();
}

int FlowOutput::type() const
{
	return Type;
}

QRectF FlowOutput::boundingRect() const
{
	auto const availableWidth = parentItem()->boundingRect().width();
	return QRectF{ availableWidth * inputRatio(_node), 0.f, availableWidth * outputRatio(_node), NODE_LINE_HEIGHT };
}

bool FlowOutput::isConnected() const
{
	return !_connections.empty();
}

QRectF FlowOutput::hotSpotBoundingRect() const
{
	auto const r = boundingRect();
	return QRectF{ r.right() - NODE_SOCKET_BOUNDING_SIZE, 0.f, NODE_SOCKET_BOUNDING_SIZE, r.height() };
}

void FlowOutput::addConnection(FlowConnection* connection)
{
	if (_connections.contains(connection))
	{
		return;
	}
	_connections.insert(connection);
	update();
}

void FlowOutput::removeConnection(FlowConnection* connection)
{
	if (!_connections.contains(connection))
	{
		return;
	}
	_connections.remove(connection);
	update();
}

FlowConnections const& FlowOutput::connections() const
{
	return _connections;
}

void FlowOutput::updateConnections()
{
	for (auto* connection : _connections)
	{
		connection->updatePath();
	}
}

void FlowOutput::paint(QPainter* painter, QStyleOptionGraphicsItem const* option, QWidget* widget)
{
	auto const hotSpot = hotSpotBoundingRect().center();
	drawOutputHotSpot(painter, hotSpot, _color, isConnected());

	auto const nameBoundingRect = boundingRect().adjusted(0.f, 0.f, -NODE_SOCKET_BOUNDING_SIZE, 0.f);

	painter->setPen(NODE_TEXT_COLOR);
	painter->setBrush(Qt::NoBrush);
	drawElidedText(painter, nameBoundingRect, Qt::AlignVCenter | Qt::AlignRight, Qt::TextElideMode::ElideMiddle, _descriptor.name);
}

} // namespace qtMate::flow
