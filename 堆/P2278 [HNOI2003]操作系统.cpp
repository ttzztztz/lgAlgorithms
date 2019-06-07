#include<iostream>
#include<queue>
using namespace std;

class Process {
public:
	int pid, priority, reachTime;
	Process() : pid(-1), priority(0), reachTime(0) {};
	Process(int _pid, int _priority, int _reachTime)
		: pid(_pid), priority(_priority), reachTime(_reachTime) {};

	bool operator< (const Process& $2) const {
		if (this->priority == $2.priority) {
			return this->pid > $2.pid;
		}
		else {
			return this->priority < $2.priority;
		}
	}
};

priority_queue<Process> CPU;
long long remainTime[10000005];

int main() {
	int pid = 0, remain = 0, priority = 0, reachTime = 0;
	long long timestamp = 0;

	while (cin >> pid >> reachTime >> remain >> priority) {
		Process task = { pid, priority,reachTime };
		remainTime[pid] = remain;

		if (CPU.empty()) {
			CPU.push(task);
		}
		else { // doing
			const Process& doingTask = CPU.top();

			if (remainTime[doingTask.pid] + timestamp <= task.reachTime) {
				cout << doingTask.pid << " " << remainTime[doingTask.pid] + timestamp << endl;
				timestamp += remainTime[doingTask.pid];
				remainTime[doingTask.pid] = 0;
				CPU.pop();

				if (
					timestamp < task.reachTime
					&& !CPU.empty()
				) {
					while (!CPU.empty() && timestamp < task.reachTime) {
						const Process& middleTask = CPU.top();
						if (timestamp + remainTime[middleTask.pid] <= task.reachTime) {
							cout << middleTask.pid << " " << remainTime[middleTask.pid] + timestamp << endl;
							timestamp += remainTime[middleTask.pid];
							remainTime[middleTask.pid] = 0;
							CPU.pop();
						}
						else {
							remainTime[middleTask.pid] -= task.reachTime - timestamp;
							timestamp = task.reachTime;
						}
					}
				}

			}
			else {
				remainTime[doingTask.pid] -= task.reachTime - timestamp;
			}

			CPU.push(task);
		}
		timestamp = task.reachTime;
	}

	while (!CPU.empty()) {
		const Process& task = CPU.top();
		timestamp += remainTime[task.pid];
		cout << task.pid << " " << timestamp << endl;
		CPU.pop();
	}

	return 0;
}
