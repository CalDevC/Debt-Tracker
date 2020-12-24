debtTracker: Account.o AccountMgr.o Global.o
	c++ main.cpp Account.o AccountMgr.o Global.o -o debtTracker
# 
# main.o: main.cpp
# 	c++ -c main.cpp

Account.o: Account.cpp
	c++ -c Account.cpp

AccountMgr.o: AccountMgr.cpp
	c++ -c AccountMgr.cpp

Global.o: Global.cpp
	c++ -c Global.cpp

clean:
	rm *.o debtTracker
