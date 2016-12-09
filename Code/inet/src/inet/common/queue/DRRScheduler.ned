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

package inet.common.queue;

//
// This module implements deficit round-robin scheduling.
// 
// There is a quantum assigned for all input queues.
// Initially each input gate gets bandwidth equal to quantum value. 
// When a packet is requested then the first input
// gate is selected that has a packet lesser than the deficit value.
// When there are waiting input packets, but there is not enough
// deficit value to schedule one, then each bucket is filled up with the
// quantum value.
// 
// This module implements the IPassiveQueue C++ interface,
// therefore it can be used as the queue component of a NIC,
// and as the input of another scheduler.
//
simple DRRScheduler
{
    parameters:
        string quantum;
        @display("i=block/subqueue");

    gates:
        input in[];
        output out;
}
