------------------------------ MODULE Ferryman ------------------------------
EXTENDS Integers, FiniteSets
\* SideOne is the side before crossing river
\* SideTwo is the side after crossing river
VARIABLES sideOne, sideTwo, ferry
Init == /\ sideOne = {"Wolf", "Goat", "Cabbage"}
        /\ sideTwo = {}
        /\ ferry = "sideOne"
FerryOneOver == \/ /\ ferry =  "sideOne"
                   /\ ferry' = "sideTwo"
                   /\ sideOne = {"Wolf", "Goat", "Cabbage"}
                   /\ sideOne' = {"Wolf","Cabbage"}
                   /\ sideTwo = {}
                   /\ sideTwo' = {"Goat"}
                \/ /\ ferry = "sideOne"
                   /\ ferry' = "sideTwo"
                   /\ sideOne = {"Wolf", "Cabbage"}
                   /\ sideOne' = {"Cabbage"}
                   /\ sideTwo = {"Goat"}
                   /\ sideTwo' = {"Wolf","Goat"}
                \/ /\ ferry = "sideOne"
                   /\ ferry' = "sideTwo"
                   /\ sideOne =  {"Goat","Cabbage"}
                   /\ sideOne' = {"Goat"}
                   /\ sideTwo = {"Wolf"}
                   /\ sideTwo' = {"Wolf","Cabbage"}
                \/ /\ ferry = "sideOne"
                   /\ ferry' = "sideTwo"
                   /\ sideOne = {"Goat"}
                   /\ sideOne' = {}
                   /\ sideTwo = {"Wolf","Cabbage"}
                   /\ sideTwo' = {"Wolf","Goat","Cabbage"}
FerryOneBack == \/ /\ ferry = "sideTwo"
                   /\ ferry' = "sideOne"
                   /\ sideOne = {"Cabbage"}
                   /\ sideOne' = {"Goat","Cabbage"}
                   /\ sideTwo = {"Wolf","Goat"}
                   /\ sideTwo' = {"Wolf"}
                \/ /\ ferry= "sideTwo"
                   /\ ferry' = "sideOne"
                   /\ sideOne = {"Wolf", "Goat"}
                   /\ sideOne' = {"Wolf"}
                   /\ sideTwo = {"Cabbage"}
                   /\ sideTwo' = {"Goat","Cabbage"}
                \/ /\ ferry = "sideTwo"
                   /\ ferry' = "sideone"
                   /\ sideOne = {}
                   /\ sideOne' = {"Goat"}
                   /\ sideTwo = {"Wolf","Goat","Cabbage"}
                   /\ sideTwo' = {"Wolf","Cabbage"}
FerryBackEmpty == \/ /\ ferry = "sideTwo"
                     /\ ferry' = "sideOne"
                     /\ sideOne = {"Wolf","Cabbage"}
                     /\ sideOne' = {"Wolf", "Cabbage"}
                     /\ sideTwo = {"Goat"}
                     /\ sideTwo' = {"Goat"}
                  \/ /\ ferry = "sideTwo"
                     /\ ferry' = "sideOne"
                     /\ sideOne = {"Goat"}
                     /\ sideOne' = {"Goat"}
                     /\ sideTwo = {"Wolf","Cabbage"}
                     /\ sideTwo' = {"Wolf","Cabbage"}
                     
Next == FerryOneOver \/ FerryOneBack \/ FerryBackEmpty


=============================================================================
\* Modification History
\* Last modified Tue Oct 25 20:03:29 PDT 2016 by NoBody
\* Created Thu Oct 20 18:14:23 PDT 2016 by NoBody
