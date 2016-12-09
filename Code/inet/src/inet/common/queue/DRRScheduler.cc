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

#include "inet/common/queue/DRRScheduler.h"
#include "inet/common/INETUtils.h"

namespace inet {

Define_Module(DRRScheduler);

DRRScheduler::~DRRScheduler()
{
    delete[] deficit;
}

void DRRScheduler::initialize()
{
    SchedulerBase::initialize();

    numInputs = gateSize("in");
    ASSERT(numInputs == (int)inputQueues.size());

    deficit = new int[numInputs];

    cStringTokenizer tokenizer(par("quantum"));
    quantum = (int)utils::atoul(tokenizer.nextToken());

    int i;
    for (i = 0; i < numInputs; ++i)
        deficit[i] = quantum;

    EV <<"Quantum Val = "<< quantum<<", numInputs = "<< numInputs;
    if (i < numInputs)
        throw cRuntimeError("Too few values given in the weights parameter. NumInputs = %d, Quantum = %d, i = %d", numInputs, quantum, i);
    if (tokenizer.hasMoreTokens())
        throw cRuntimeError("Too many values given in the deficit parameter.");
}

bool DRRScheduler::schedulePacket()
{
    bool allQueueIsEmpty = true;
    int curPktLen = 0;
    for (int i = 0; i < numInputs; ++i) {
        if (!inputQueues[i]->isEmpty()) {
            allQueueIsEmpty = false;
            cPacket *packet = check_and_cast<cPacket *>(inputQueues[i]->peek());
            curPktLen = packet->getByteLength();
            EV <<"Quantum Val = "<< quantum<<", curPktLen = "<< curPktLen<< ", Deficit value = " << deficit[i] << endl;
            if(deficit[i] >= curPktLen) {
                deficit[i] -= curPktLen;
                inputQueues[i]->requestPacket();
                return true;
            }
        }
    }

    if (allQueueIsEmpty)
        return false;

    // Round ended. Refill deficit counter
    bool packetRequested = false;
    for (int i = 0; i < numInputs; ++i) {
        deficit[i] += quantum;
        EV <<"Quantum Val Refreshed for queue[ "<< i<<" ], deficit new value = "<< deficit[i] << endl;
        if (!packetRequested && deficit[i] > 0 && !inputQueues[i]->isEmpty()) {
            cPacket *packet = check_and_cast<cPacket *>(inputQueues[i]->peek());
            curPktLen = packet->getByteLength();
            if(deficit[i] >= curPktLen) {
                deficit[i] -= curPktLen;
                inputQueues[i]->requestPacket();
                packetRequested = true;
            }
        }
    }
    return packetRequested;
}



} /* namespace inet */
