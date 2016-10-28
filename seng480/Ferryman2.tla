----------------------------- MODULE Ferryman2 -----------------------------
EXTENDS Integers, FiniteSets
CONSTANTS Wolf, Goat, Cabbage
CREATURES == {Wolf, Goat, Cabbage}
VARIABLES left, right,ferry
Init == /\ left=CREATURES
        /\ right={}
        /\ ferry = "left"
alone(animals,side,f) == (animals \in SUBSET side) /\ ~ferry=f
danger(sideOne,sideTwo) == \/ alone({Wolf,Goat},sideOne,"right")
                           \/ alone({Wolf,Goat},sideTwo,"left")
                           \/ alone({Goat,Cabbage},sideOne,"right")
                           \/ alone({Goat,Cabbage},sideTwo,"left")
safe(l,r)== ~danger(l,r)

FerryOneOver == \/ /\ ferry="left"
                   /\ ferry'="right"
                   /\ left' \in SUBSET left
                   /\ Cardinality(left') = Cardinality(left)-1
                   /\ right' = CREATURES \ left'
                   /\ safe(left',right')
                \/ /\ ferry="right"
                   /\ ferry'="left"
                   /\ right' \in SUBSET right
                   /\ Cardinality(right') = Cardinality(right)-1
                   /\ left \in SUBSET CREATURES
                   /\ left' =CREATURES \ right'
                   /\ safe(left',right')
CrossEmpty == \/ /\ ferry="right"
                 /\ ferry'="left"
                 /\ left' = left
                 /\ right' = right
                 /\ safe(left,right)
              \/ /\ ferry="left"
                 /\ ferry'="right"
                 /\ left' = left
                 /\ right' = right
                 /\ safe(left,right)
Next == FerryOneOver \/ CrossEmpty

=============================================================================
\* Modification History
\* Last modified Wed Oct 26 16:02:17 PDT 2016 by NoBody
\* Created Tue Oct 25 19:59:47 PDT 2016 by NoBody
