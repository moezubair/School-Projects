----------------------------- MODULE Ferryman3 -----------------------------
CONSTANTS Wolf, Goat,Cabbage
CREATURES== {Wolf,Goat, Cabbage}

(************************************************
--algorithm RiverCrossing {
   variables left = CREATURES; right = {}; ferry="left";
   {while (right /= CREATURES) {
    if (ferry="left"){
        left = \in SUBSET left
        right = CREATURES \ left
        ferry:= "right"
        
    }else if (ferry="right"){
        ferry:="left"
    }
   }}       
}

*************************************************)
\* BEGIN TRANSLATION
VARIABLES left, right, ferry, pc

vars == << left, right, ferry, pc >>

Init == (* Global variables *)
        /\ left = CREATURES
        /\ right = {}
        /\ ferry = "left"
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ IF right /= CREATURES
               THEN /\ IF ferry="left"
                          THEN /\ ferry' = "right"
                          ELSE /\ IF ferry="right"
                                     THEN /\ ferry' = "left"
                                     ELSE /\ TRUE
                                          /\ ferry' = ferry
                    /\ pc' = "Lbl_1"
               ELSE /\ pc' = "Done"
                    /\ ferry' = ferry
         /\ UNCHANGED << left, right >>

Next == Lbl_1
           \/ (* Disjunct to prevent deadlock on termination *)
              (pc = "Done" /\ UNCHANGED vars)

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION
=============================================================================
\* Modification History
\* Last modified Fri Oct 28 09:52:52 PDT 2016 by NoBody
\* Created Thu Oct 27 11:42:29 PDT 2016 by NoBody
