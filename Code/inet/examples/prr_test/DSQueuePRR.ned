//
// Copyright (C) 2012 Opensim Ltd.
// Author: Tamas Borbely
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.examples.diffserv.prr_test;

import inet.common.queue.DropTailQueue;
import inet.common.queue.IOutputQueue;
import inet.common.queue.PriorityScheduler;
import inet.networklayer.diffserv.BehaviorAggregateClassifier;


//
// Diffserv Queue used in Experiment 1.1 - 1.6 and 5.1.
//
module DSQueuePRR like IOutputQueue
{
    parameters:
        int frameCapacity = default(100);

    gates:
        input in;
        output out;

    submodules:
        classifier: BehaviorAggregateClassifier {
            dscps = "EF AF11 AF21 AF31 AF41";
            @display("p=41,284");
        }
        efQueue: DropTailQueue {
            frameCapacity = frameCapacity;
            @display("p=195,95");
        }
        af1xQueue: DropTailQueue {
            frameCapacity = frameCapacity;
            @display("p=195,204");
        }
        af2xQueue: DropTailQueue {
            frameCapacity = frameCapacity;
            @display("p=189,284");
        }
        af3xQueue: DropTailQueue {
            frameCapacity = frameCapacity;
            @display("p=195,368");
        }
        af4xQueue: DropTailQueue {
            frameCapacity = frameCapacity;
            @display("p=195,446");
        }
        beQueue: DropTailQueue {
            frameCapacity = frameCapacity;
            @display("p=195,535");
        }
        prr: PriorityScheduler {
            @display("p=384,368");
        }


    connections:
        in --> classifier.in;
        classifier.outs++ --> efQueue.in;
        classifier.outs++ --> af1xQueue.in;
        classifier.outs++ --> af2xQueue.in;
        classifier.outs++ --> af3xQueue.in;
        classifier.outs++ --> af4xQueue.in;
        classifier.defaultOut --> beQueue.in;

        af1xQueue.out --> prr.in++;
        af2xQueue.out --> prr.in++;
        af3xQueue.out --> prr.in++;
        af4xQueue.out --> prr.in++;
        beQueue.out --> prr.in++;
        efQueue.out --> prr.in++;
        prr.out --> out;

}

