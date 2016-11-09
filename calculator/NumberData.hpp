#pragma once

#include "nodeEditor/NodeDataModel.hpp"

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class NumberData : public NodeData
{
public:

  NumberData()
    : _number(0.0)
  {}

  NumberData(double const number)
    : _number(number)
  {}

  NodeDataType type() const override
  {
    return NodeDataType {"number",
                         "Number"};
  }

  double number() const
  { return _number; }

  QString numberAsText() const
  { return QString::number(_number, 'f'); }

private:

  double _number;
};
