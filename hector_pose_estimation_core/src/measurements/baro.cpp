//=================================================================================================
// Copyright (c) 2011, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#include <hector_pose_estimation/measurements/baro.h>

namespace hector_pose_estimation {

BaroModel::BaroModel()
{
  qnh_ = 1013.25;
  parameters().add("qnh", qnh_);
}

BaroModel::~BaroModel() {}

ColumnVector BaroModel::ExpectedValueGet() const
{
  y_(1) = qnh_ * pow(1.0 - (0.0065 * (x_(POSITION_Z) + elevation_)) / 288.15, 5.255);
  return y_;
}

Matrix BaroModel::dfGet(unsigned int i) const
{
  C_(1,POSITION_Z) = qnh_ * 5.255 * pow(1.0 - (0.0065 * (x_(POSITION_Z) + elevation_)) / 288.15, 4.255) * (-0.0065 * (x_(POSITION_Z) + elevation_));
  return C_;
}

void Baro::reset(const StateVector& state)
{
  setElevation(state(POSITION_Z) + getElevation());
}

} // namespace hector_pose_estimation
