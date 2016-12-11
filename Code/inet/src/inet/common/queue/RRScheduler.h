//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __INET_RRSCHEDULER_H
#define __INET_RRSCHEDULER_H

#include "inet/common/INETDefs.h"
#include "inet/common/queue/SchedulerBase.h"

namespace inet {
/**
 * This module implements a Deficit Round Robin Scheduler.
 */

class INET_API RRScheduler: public SchedulerBase
{
protected:
   int numInputs;    // number of input gates
   unsigned long long int currQueueIndex; // Next queue to be served

public:
    RRScheduler():numInputs(0), currQueueIndex(0) {}

protected:
   virtual ~RRScheduler();
   virtual void initialize() override;
   virtual bool schedulePacket() override;

};

} /* namespace inet */

#endif /* __INET_RRSCHEDULER_H */
