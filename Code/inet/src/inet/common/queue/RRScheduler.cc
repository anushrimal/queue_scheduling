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

#include "inet/common/queue/RRScheduler.h"
#include "inet/common/INETUtils.h"

namespace inet {

Define_Module(RRScheduler);

RRScheduler::~RRScheduler()
{}

void RRScheduler::initialize()
{
    SchedulerBase::initialize();

    numInputs = gateSize("in");
    ASSERT(numInputs == (int)inputQueues.size());
    currQueueIndex = 0;
}

bool RRScheduler::schedulePacket()
{
    bool allQueueIsEmpty = true;
    int i = 0, j = 0;
    for (currQueueIndex, j = 0; i < numInputs && j < numInputs; ++j) {
        if (!inputQueues[(currQueueIndex % numInputs)]->isEmpty()) {
            allQueueIsEmpty = false;
            EV <<"Returned packet from queue index [= "<< (currQueueIndex % numInputs) <<"]";
            inputQueues[(currQueueIndex % numInputs)]->requestPacket();
            currQueueIndex++;
            return true;
        } else {
            currQueueIndex++;
        }
    }
    if (allQueueIsEmpty)
        return false;

}



} /* namespace inet */
