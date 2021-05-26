#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SLEEP_TIME 60

int pomodoroTimer(int workMins, int breakMins) {
	int currentMins, isBreak;
	isBreak = 0;
	currentMins = 0;
	while(1) {
		system("clear");
		if(isBreak == 1) {
			if(currentMins >= breakMins) {
				printf("Time to work!\nPress ENTER to start work period, or press CTRL+C to exit.\n");
				system("osascript -e 'display notification with title \"Time to work!\"' && afplay /System/Library/Sounds/Glass.aiff");
				getchar();
				isBreak = 0;
				currentMins = 0;
				continue;
			} else {
				printf("Break period (%d minute%s)\n%d minute%s left\nPress CTRL+C to exit.\n", breakMins, (breakMins == 1) ? "" : "s", breakMins-currentMins, (breakMins-currentMins == 1) ? "" : "s");
			}
		} else {
			if(currentMins >= workMins) {
				printf("Time for a break!\nPress ENTER to start break, or press CTRL+C to exit.\n");
				system("osascript -e 'display notification with title \"Time for a break!\"' && afplay /System/Library/Sounds/Glass.aiff");
				getchar();
				isBreak = 1;
				currentMins = 0;
				continue;
			} else {
				printf("Work period (%d minute%s)\n%d minute%s left\nPress CTRL+C to exit.\n", workMins, (workMins == 1) ? "" : "s", workMins-currentMins, (workMins-currentMins == 1) ? "" : "s");
			}
		}
		currentMins++;
		sleep(SLEEP_TIME);
	}
	
	return 0;
}

int usage() {
	printf("usage: pom <work minutes> <break minutes>\n");
	return 0;
}

int fatalError(char* message) {
	printf("fatal error: %s\n", message);
	return 0;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		return usage();
	}
	
	int workMins = atoi(argv[1]);
	int breakMins = atoi(argv[2]);
	
	if(workMins == 0 || breakMins == 0) {
		return fatalError("you must enter a number");
	}
	
	return pomodoroTimer(workMins, breakMins);
	
	return 0;
}