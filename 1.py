#!/usr/bin/env python

#By Aloysius Chia (1547098)
#DISM/FT/2A/21
#PSE Assignment 2: Word Game Phase 1

import random
import re
import signal
import time
TIMEOUT = 20
PENALTY = 20
MAXROUND = 15
RESPONSE_LIMIT = 13
FAST_LIMIT = 7
FAST_BONUS = 10
# below is a list of ubuntu termal font control sequence
HEADER = '\033[95m'
BLU = '\033[94m'   # display subsequent output in BLUE 
GRN = '\033[92m'   # display subsequent output in GREEN
RED = '\033[31m'   # display subsequent output in RED 
FAIL = '\033[91m'
ENDC = '\033[0m'   # end of the special font control. 
BOLD = '\033[1m'
UNDERLINE = '\033[4m'
# Skelton for the ST2512 word game assignment.
# word game in Python
# single player game
# 
def interrupted(signum, frame):
    # raise a ValueError to break a blocked i/o call.
    # for example: raw_input()
    raise ValueError("interrupted")
    

def my_raw_input(prompt,defval=None):
    # my_raw_input, provide a timed raw_input function.
    # in case the user fails to enter any value by the given time.
    # it will return None.
    
    # Setup alarm handling function to be "interrupted"
    signal.signal(signal.SIGALRM, interrupted)
    # starts an alarm, to be signaled in 20 seconds
    signal.alarm(TIMEOUT)
    try:
            name = raw_input(prompt)
            # clear the alarm
            signal.alarm(0)
            return name
    except:
            # timeout, only return the default value.
            return defval    

def showmenu():
    # prints the help menu
    print """
    This game begins with showing the player a randomly picked word
    The player and the computer will take turns to enter a new word to replace the
    current word according to the game rules.
    Repeat the above process to earn scores untl the game is terminated.
    The game will be terminated when the player fails to enter an acceptable word
    within 20 seconds or when the game completes the 15th round.
    
    Acceptance Rules for a new word: 
     .The minimum length of the word is 6 letters.
     .All letters in the word must be in lowercases.
     .It is listed in the internal dictionary. 
     .It has not been entered at the same play session.
     .It must begin with the last letter of the current word.
     .It cannot be ended with -ing-.

    Scoring Rules:
    
    word bonus: Each letter in the new word earns points based on the following point values:
    
        (1 point)-a, e, i, o, u, l, n, s, t, r.
        (2 points)-d, g.
        (3 points)-b, c, m, p.
        (4 points)-f, h, v, w, y.
        (5 points)-k.
        (8 points)- j, x.
        (10 points)-q, z.

    speed bonus: Additonal 10 bonus points will be added if the response time is less than 7 seconds.

    Slow reponse penalty: no point will be  awarded if the response time is longer than
    13 seconds.

    Invalid word penalty : -20 points and the game ends immediately.

    Timeout penalty : -20 points and the game ends immediately.
    
    """
    raw_input("Press <Enter Key> to exit help")
    
def findword(oldword,fulldict,owndict):
    # Simulation of how the computer to find a suitable word
    # It will return a new word, which is
    # beginning with the last letter of 'oldword,
    # it is found from the fulldict,
    # it is not found in the owndict
    # In case the function cannot find a word to fulfill the above condition,
    # it will return a None.
    lastChar = oldword[-1:]
    
    # Generate a list of words starting with the last character
    sortedList = [word for word in fulldict if lastChar == word[0] and word not in owndict]

    for word in sortedList:
        newWord = random.choice(sortedList)
        if (newWord in fulldict):
            return newWord

    # if sutiable no word is found        
    return None
    
def loadwords(wordlistfile):
    newdict = {}
    f=open(wordlistfile,"r")
    # load in all the words from the wordlistfile to the newdict.
    for line in f:
        if (line[-1:] == "\n"):
            line = line[:-1]
        if (len(line) > 5 and line[-3:] != "ing" and "'" not in line):
            newdict[line] = 1    

    f.close()
    
    return newdict

def isValid(newword,oldword,fulldict,owndict):
    #This function validates if the newword is fulfilling all the
    #rules.
    # It returns a tuple of two items.
    # The first item is either True or False, the second item provides the descriptions
    # for example, it may return (False, "Invalid word. It is shorter than 6 letters")
    if len(newword) < 6:
        return False, "Invalid word. It is shorter than 6 letters"
    if(newword != newword.lower()):
        return False, "Input was not in lowercase"
    if (newword not in fulldict.keys()):
        return False, "Input not found in dictionary"
    if (newword in owndict.keys()):
        return False, "Input has been used"
    if (newword[0] != oldword[-1:]):
        return False, "Input does not end with last character of previous word"
    if (newword[-3:] == "ing"):
        return False, "Input is ending with -ing-"

    return True, "The new word is accepted"
def get_score_map():
    #utility function to provide the score map
    
    smap = {}
    for c in "aeioulnstr":
        smap[c]=1
    for c in "dg":
        smap[c]=2
    for c in "bcmp":
        smap[c]=3
    for c in "fhvwy":
        smap[c]=4
    for c in "k":
        smap[c]=5
    for c in "jx":
        smap[c]=8
    for c in "qz":
        smap[c]=10       
    return smap

def compute_score(thisword,scoremap):
    # based on the scoremap, compute the score of thisword.
    # It also needs to generate the score string and return it to the caller.
    # Its return value is a tuple with the score and the discription
    # for exmaple : ( 11, "e(1)+ n(1)+ g(2)+ l(1)+ i(1)+ s(1)+ h(4) = 11")

    total = 0
    score_str = ""
    
    # get the score map
    scoreMap = get_score_map()
    
    # calculating score and generating score string
    for c in thisword:
        if (c != "\n"):
            total = total + scoreMap[c]
            score_str = score_str + c + "(" + str(scoreMap[c]) + ")+ "

    # completing score string
    score_str = score_str[:-2] +  " = " + str(total)

    return total,score_str

def finalScores(players):
    # function to print final scores
    result = "\n\nThe final scores:\n"
    # print final results
    result = result + players[0]["name"] + ": " +str(players[0]["score"]) + ".\n"
    result = result + players[1]["name"] + ": " + str(players[1]["score"]) + ".\n"
     
    return result

def playgame(maindict):
    print """
    +-------------------------------+
    | Welcome to ST2512 Playground! |
    +-------------------------------+
    """
    cmd=""
    while cmd != 's':
        cmd = my_raw_input("Type [s]tart to start, [h]elp for help or [q]uit =>","q")
        if cmd == 'h':
            showmenu()
        elif cmd == 'q':
            return
    # The game starts here...
    round = 1    
    score_map = get_score_map()
    mydict = {} # declare a new dict to keep track of all the words used in the play session.
    curword = random.choice(maindict.keys()) # picking the initial word
    mydict[curword] = 1    # add in the first word into mydict
    players=[]             # players[0] stores the player's info. players[1] stores the computer score
    
    player = {}
    computer = {}
    # prompt for the user name
    pname = my_raw_input("Player name=>","Anonymous")
    
    player["name"]=pname
    player["score"] = 0
    players.append(player)
    
    pname = "BetaGone" # hardcoded the computer name to be 'BetaGone'
    computer["name"]=pname
    computer["score"] = 0
    players.append(computer)
    
    while True:
        print "\nAt Round {0}".format(round)
        print players[0]["name"]," scores:" , players[0]["score"],"   ",
        print players[1]["name"]," scores:", players[1]["score"]
        if round == 1:
            print "Current word: {0}{1}{2}".format(BLU,curword,ENDC)
        # For each round, the player will go first, then will be the computer's turn    
        pnum=0
        startAt = time.time() # set startAt to the dummy value of 0 for demo purpose
        # modify startAt to store the current time.
        input= my_raw_input(players[pnum]["name"]+"'s turn =>")
        if input == None:
            print "\n{0}Input time out.{1}".format(RED,ENDC)
            players[pnum]["score"] = players[pnum]["score"] - PENALTY
            break
        duration = (time.time() - startAt)     
        
        print "{0}Response time : {1:0.2f} s.{2}".format(GRN,duration,ENDC)
        # modify durtation to store the current time - startAt to
        # get the player's response time (in seconds)
        isok, mesg = isValid(input,curword,maindict,mydict)
        if not isok:
            print "{0}{1}{2}".format(RED,mesg,ENDC)
            players[pnum]["score"] = players[pnum]["score"] - PENALTY
            break
        # The input is accepted.
        # need to compute the score
        c_score,score_str=compute_score(input,score_map)
        print score_str
        if duration <=FAST_LIMIT:
            print "{0}Speed bouns - extra {1} points{2}.".format(GRN,FAST_BONUS,ENDC)
            c_score = c_score + FAST_BONUS
        elif duration > RESPONSE_LIMIT:
            print "{0}Reponse too slow, no point will be awarded this round.{1}".format(RED,ENDC)
            c_score = 0
        players[pnum]["score"] = players[pnum]["score"] + c_score
        # add the input into mydict
        mydict[input] = 1
        # replace curword with input
        curword = input
        
        #computer's turn
        pnum=1
        input = findword(curword,maindict,mydict)
        print "Computer's turn => {0}{1}{2}".format(BLU,input,ENDC)
        if input:
            c_score,score_str=compute_score(input,score_map)
            print score_str
            players[pnum]["score"] = players[pnum]["score"] + c_score
            # add the input into mydict
            mydict[input] = 1
            curword = input
        else:
            # extremely unlikely case, the computer cannot find a matching word!
            print "WOW ! {0} fails to answer".format(players[pnum]["name"])
            break
        round=round+1
        if (round > MAXROUND):
            # the game ends at round 15.
            break
    # end of while loop
    # now is time to show the final scores

    print "{0}{1}{2}".format(BLU,finalScores(players),ENDC)
    
    if (players[0]["score"]==players[1]["score"]):
        print "Wow, what a close fight, both of you are winners!"
    elif (players[0]["score"]<players[1]["score"]):
        print players[0]["name"]+ " , you have put up a good fight, try harder next time."
    else:
        print "Congratulation to "+players[0]["name"]+ " , you are the champion!"
          
    
#main program start here

# setup the main dictionary , maindict
maindict = loadwords("wordlist.txt")
# invoke the game play with the maindict
playgame(maindict)
print "\nSee you again Soon."
