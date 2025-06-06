% Data-driven concurrent version
%Roberto Sergio Ribeiro de Meneses - 520403
%Guilherme Galvao Serra - 520402
declare Pipe
fun {Pipe Xs L H F}
    if L=<H then {Pipe {F Xs L} L+1 H F} else Xs end
end

declare Josephus2 Victim
fun {Josephus2 N K}
    fun {Victim Xs I}
        case Xs of kill(X S)|Xr then
            if S==1 then Last=I nil
            elseif X mod K==0 then
                kill(X+1 S-1)|Xr
            else
                kill(X+1 S)|{Victim Xr I}
            end
        [] nil then nil end
    end
    Last Zs
    in
        Zs={Pipe kill(1 N)|Zs 1 N
        fun {$ Is I} thread {Victim Is I} end end}
        Last
    end