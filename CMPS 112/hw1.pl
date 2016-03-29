% Ryan Coley
% hw1.pl

% Rules and Predicates for 9-11
father(al, bud).
father(al, kelly).
father(al, bob).

father(james, charlotte).

mother(peggy, kelly).
mother(peggy, bud).
mother(peggy, sue).

mother(martha, peggy).
mother(charlotte,al).

% 9
grandma(X,Y):- mother(X,Z), mother(Z,Y).
grandma(X,Y):- mother(X,Z), father(Z,Y).

% 10
descendents(X,Y):- mother(X,Y).
descendents(X,Y):- father(X,Y).
descendents(X,Y):- (mother(X,Z);father(X,Z)),descendents(Z,Y).

% 11
siblings(X,Y):- mother(M,X),mother(M,Y),X\=Y.
siblings(X,Y):- father(F,X),father(F,Y),X\=Y.

% 12
% Rules and Predicates
%  ->(q0)  ---a-->  (q1)  ---b-->  (q2*)
%     |
%     a
%     |
%     V  / --<-- \
%    (q3*)        a
%        \ -->-- /
transition(q0,q1,a).
transition(q1,q2,b).
transition(q0,q3,a).
transition(q3,q3,a).
accepting(q2).
accepting(q3).

ableToMove(State, []):- accepting(State).
ableToMove(State, [H|T]):- transition(State,X,H),ableToMove(X,T).
accepts(State, InputList):- ableToMove(State, InputList).