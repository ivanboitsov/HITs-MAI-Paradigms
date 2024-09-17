% Боги
god(trust).
god(diplomacy). 
god(lie).

% Значение ответов богов
answer(trust, True, True). % Бог правды говорит только правду
answer(diplomacy, _, _). % Бог дипломатии может говорить и правду и ложь
answer(lie, True, Lie):- not(True=Lie). % Бог лжи говорит только неправду

unique([]) :- !.
unique([A|B]) :- member(A, B), !, fail; unique(B).

% Определение позиций, исходя из условий задачи
positions(X,Y,Z):-
    god(X), god(Y), god(Z), unique([X, Y, Z]),
    
    % Ответы богов смельчаку
    answer(X, Y, trust),
    answer(Y, Y, diplomacy),
    answer(Z, Y, lie).