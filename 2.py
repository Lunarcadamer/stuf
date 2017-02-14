#!/usr/bin/env python
import wgengine
import socket
import threading
import Queue
import random
import time

TIMEOUT = 20
PENALTY = 20
MAXROUND = 15
RESPONSE_LIMIT=13
FAST_LIMIT = 7
FAST_BONUS = 10

class BColors:
    HEADER = '\033[95m'
    BLU = '\033[94m'
    GRN = '\033[92m'
    RED = '\033[31m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def usersTurn(con,maindict,engine,buf):
    GRN=BColors.GRN
    RED=BColors.RED
    BLU=BColors.BLU
    ENDC=BColors.ENDC
    pnum=0
    startAt = time.time()
    input = con.recv(255)
    buf = ""
    if input == None:
        buf = "\n{0}Input time out.{1}".format(RED,ENDC)
        engine.players[pnum]["score"] = engine.players[pnum]["score"] - PENALTY
        #con.send(buf)
        return False
    duration = time.time() - startAt
    buf = buf + "response time : {0:0.2f} s".format(duration)
    isok, mesg = engine.isValid(input,maindict)
    if (not isok):
        buf = "{0}{1}{2}".format(RED,mesg,ENDC)
        #con.send(buf)
        engine.players[pnum]["score"] = engine.players[pnum]["score"] - PENALTY
        return False
    # The input is accepted.
    # need to compute the score
    c_score,score_str=engine.compute_score(input)
    buf = buf + "\n" + score_str
    if duration <=FAST_LIMIT:
        buf = buf + "\n{0}Speed bonus - extra {1} points awarded.{2}".format(GRN,FAST_BONUS,ENDC)
        c_score = c_score + FAST_BONUS
    elif duration > RESPONSE_LIMIT:
        buf = buf + "\n{0}Response too slow. No point will be awarded.{1}".format(RED,ENDC)
        c_score = 0
    engine.players[pnum]["score"] = engine.players[pnum]["score"] + c_score
    # add the input into mydict
    engine.add_used_word(input)
    # replace curword with input
    engine.curword = input
    #con.send(buf)

    pnum=1
    engine.oldword = engine.curword
    input = engine.findword(maindict.mDict)
    buf = buf + "\n" + "\n{0}'s turn => {1}{2}{3}".format(engine.players[pnum]["name"],BLU,input,ENDC)
    if input:
        c_score,score_str=engine.compute_score(input)
        buf = buf + "\n" + score_str + "\n"
        engine.players[pnum]["score"] = engine.players[pnum]["score"] + c_score
        # add the input into mydict
        engine.add_used_word(input)
        engine.curword = input
        buf = buf + "\nAt Round    " + str(engine.round + 1) + "\n" + engine.players[0]['name'] + " scores:    " + str(engine.players[0]['score']) + "   " + engine.players[1]["name"] + " scores:    " + str(engine.players[1]["score"]) + "\n"
        con.send(buf)
    else:
        # special case, the computer cannot find a suitable word.
        return False
    return True

def handler(con,q,maindict):
    con.settimeout(20.0)
    GRN=BColors.GRN
    RED=BColors.RED
    BLU=BColors.BLU
    ENDC=BColors.ENDC

    engine = wgengine.WGEngine()
    
    engine.players= { 0:{}, 1:{}}
    engine.players[0]['name'] = 'Anonymous'
    engine.players[0]['score'] = 0
        
    engine.players[1]['name'] = 'BetaGone'
    engine.players[1]['score'] = 0
    while True:
        try:
            engine.curword = random.choice(maindict.mDict.keys())
            engine.add_used_word(engine.curword)
            
            pname = con.recv(255)
    	    engine.players[0]["name"] = pname

            while True:
                buf = "\nAt Round    " + str(engine.round) + "\n" + engine.players[0]['name'] + " scores:    " + str(engine.players[0]['score']) + "   " + engine.players[1]["name"] + " scores:    " + str(engine.players[1]["score"])
                
                if engine.round == 1:
                    buf = buf + "\nCurrent word: {0}{1}{2}\n".format(BLU,engine.curword,ENDC)
                    con.send(buf)
                    buf = ""
                if not usersTurn(con,maindict,engine,buf):
                    break
                #if not computersTurn(con,maindict,engine,buf):
                #    break
                engine.round=engine.round+1
                if engine.round>MAXROUND:
                    break                     # game ends at 30th round
            # end of while loop
            
            print "{0}{1}{2}".format(BLU,engine.get_final_scores(),ENDC)
            if engine.isDrawn():
                print "Wow, what a close fight, both of you are winners!"
            elif engine.isPlayerWon():
                print "Congratulation to "+engine.players[0]["name"]+ " , you are the champion!"
            else:
                print engine.players[0]["name"]+ " , you have put up a good fight, try harder next time."
    	    
    	except Exception as inst:
            if stopFlag or (str(inst) != "timed out"):
    		q.put("q")
    		break
	#con.close()
	print "client connection is closed"
	return

maindict = wgengine.MainDict()
commonq = Queue.Queue(10)
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind(('localhost', 8888))
serversocket.listen(5) # become a server socket, maximum 5 connections
print "Server starts listening ..."
client=0
stopFlag=False
serversocket.settimeout(3.0) # setup a 3 seconds timeout to exit the blocking state
while True:
    if not stopFlag:
    	try:
            connection, address = serversocket.accept() 
            print "start a new connection"
            client=client+1
            # setup and start a new thread to run an instance of handler() 
            t = threading.Thread(target=handler, args=(connection,commonq,maindict))
            t.start()
    	except Exception as inst:
            if str(inst) != "timed out": # timed out exception is okay, else must quit.
                break
        else:
            if client == 0:
                break	
	# exit from the accpet() blockage, time to check the Queue. 
        if not commonq.empty():
            data = commonq.get()
            client = client - 1
            print data + ':'+ str(client)
	    if data == 'x':
                stopFlag = True
		
print "Server stops"
