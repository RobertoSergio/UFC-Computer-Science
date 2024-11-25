%Roberto Sergio Ribeiro de Meneses - 520403
%Guilherme Galvao Serra - 520402
declare
local
   fun {NotLoop Xs}
      case Xs of X|Xr then (1-X)|{NotLoop Xr} end
   end
in
   fun {NotG Xs}
      thread {NotLoop Xs} end
   end
end

fun {GateMaker F}
   fun {$ Xs Ys}
      fun {GateLoop Xs Ys}
	 case Xs#Ys of (X|Xr)#(Y|Yr) then
	    {F X Y}|{GateLoop Xr Yr}
	 end
      end
   in
      thread {GateLoop Xs Ys} end
   end
end

AndG = {GateMaker fun {$ X Y} X*Y end}
OrG = {GateMaker fun {$ X Y} X+Y-X*Y end}
NandG = {GateMaker fun {$ X Y} 1-X*Y end}
NorG = {GateMaker fun {$ X Y} 1-X-Y+X*Y end}
XorG = {GateMaker fun {$ X Y} X+Y-2*X*Y end}


declare proc {Subtrator A B Tin ?S ?Tout}
	   K L M N
	in
	   S={XorG A {XorG B Tin}}
	   K={AndG {NotG A} B}
	   L={AndG {NotG A} Tin}
	   M={AndG B Tin}
	   N={OrG K L}
	   Tout={OrG N M}
	end

declare proc {Subtrator5bits A B Tin ?S ?Tout}
	   A1 A2 A3 A4 A5 B1 B2 B3 B4 B5 S1 S2 S3 S4 S5 C1 C2 C3 C4 C5
	in
	   case A
	   of nil then A1 = 0|_
	   [] A|Ar then A1 = A|_
	      case Ar
	      of nil then A2 = 0|_
	      [] Ar|As then A2 = Ar|_
		 case As
		 of nil then A3 = 0|_
		 [] As|At then A3 = As|_
		    case At
		    of nil then A4 = 0|_
		    [] At|Af then A4 = At|_
		       case Af
		       of nil then A5 = 0|_
		       [] Af|Au then A5 = Af|_
		       [] Af|nil then A5 = Af|_
		       end
		    end
		 end
	      end
	   end
	   case B
	   of nil then B1 = 0|_
	   [] B|Br then B1 = B|_
	      case Br
	      of nil then B2 = 0|_
	      [] Br|Bs then B2 = Br|_
		 case Bs
		 of nil then B3 = 0|_
		 [] Bs|Bt then B3 = Bs|_
		    case Bt
		    of nil then B4 = 0|_
		    [] Bt|Bf then B4 = Bt|_
		       case Bf
		       of nil then B5 = 0|_
		       [] Bf|Bu then B5 = Bf|_
		       [] Bf|nil then B5 = Bf|_
		       end
		    end
		 end
	      end
	   end
	   {Subtrator A5 B5 Tin S1 C1}
	   {Subtrator A4 B4 C1 S2 C2}
	   {Subtrator A3 B3 C2 S3 C3}
	   {Subtrator A2 B2 C3 S4 C4}
	   {Subtrator A1 B1 C4 S5 C5}
	   S = [S5 S4 S3 S2 S1]
	   Tout = C5
	end

declare
   proc {IsPrime5Bits X ?R}
      K L M N O And1 And2 And3 And4 And5 And6 And7 And8 And9 And10 And11 And12 And13 And14 And15 And16 And17 And18 And19 And20 Or1 Or2 Or3 Or4 Or5 Or6 Or7 Or8 Or9
   in
      case X
      of nil then K = 0|_
      [] X|Xr then K = X|_
         case Xr
         of nil then L = 0|_
         [] Xr|Xs then L = Xr|_
            case Xs
            of nil then M = 0|_
            [] Xs|Xt then M = Xs|_
               case Xt
               of nil then N = 0|_
               [] Xt|Xf then N = Xt|_
                  case Xf
                  of nil then O = 0|_
		  [] Xf|Xu then O = Xf|_
		  [] Xf|nil then O = Xf|_
		  end
	       end
	    end
	 end
      end
      
      And1 = {AndG {NotG K} {NotG  L}}
      And2 = {AndG And1 M}
      And3 = {AndG {NotG L} M}
      And4 = {AndG And3 N}
      And5 = {AndG {NotG K} L}
      And6 = {AndG And5 N}
      And7 = {AndG {NotG M} L}
      And8 = {AndG And7 N}
      And9 = {AndG {NotG K} O}
      And10 = {AndG And9 L}
      And11 = {AndG And10 M}
      And12 = {AndG And11 N}
      And13 = {AndG {NotG L} O}
      And14 = {AndG And13 M}
      And15 = {AndG And14 N}
      And16 = {AndG {NotG M} O}
      And17 = {AndG And16 N}
      And18 = {AndG {NotG N} O}
      And19 = {AndG {NotG K} And3}
      And20 = {AndG And19 O}
                        
      Or1 = {OrG And2 And4}
      Or2 = {OrG And6 And8}
      Or3 = {OrG And10 And11}
      Or4 = {OrG And12 And14}
      Or5 = {OrG And15 And17}
      Or6 = {OrG Or1 And20}
      Or7 = {OrG Or2 Or3}
      Or8 = {OrG Or4 Or5}
      Or9 = {OrG Or6 Or7}
						       
      R = {OrG  Or8 Or9}
      case R
      of 1|_ then {Browse inp(X)#ehprimo}
      [] 0|_ then {Browse inp(X)#naoprimo}
      end
   end

declare
   proc {Sequencia_de_1_7bits X ?R}
      K L M N O P Q  And1 And2 And3 And4 And5 And6 Or1 Or2 Or3 Or4
   in
      case X
      of nil then K = 0|_
      [] X|Xr then K = X|_
         case Xr
         of nil then L = 0|_
         [] Xr|Xs then L = Xr|_
            case Xs
            of nil then M = 0|_
            [] Xs|Xt then M = Xs|_
               case Xt
               of nil then N = 0|_
               [] Xt|Xf then N = Xt|_
                  case Xf
                  of nil then O = 0|_
		  [] Xf|Xu then O = Xf|_
		     case Xu
		     of nil then P=0|_
		     [] Xu|Xv then P=Xu|_
			case Xv
			of nil then Q=0|_
			[] Xv|Xw then Q=Xv|_
			[] Xv|nil then Q = Xv|_
			end
		     end
		  end
	       end
	    end
	 end
      end
      
      And1 = {AndG K L}
      And2 = {AndG L M}
      And3 = {AndG M N}
      And4 = {AndG N O}
      And5 = {AndG O P}
      And6 = {AndG P Q}
      
      Or1 = {OrG And1 And2}
      Or2 = {OrG Or1 And3}
      Or3 = {OrG Or2 And4}
      Or4 = {OrG Or3 And5}
      
      R  = {OrG Or4 And6}

      case R
      of 1|_ then {Browse inp(X)#tem_1_em_sequencia}
      [] 0|_ then {Browse inp(X)#nao_tem_1_em_sequencia}
      end
      
   end

%Subtratorde5Bits
declare
A= 1|0|1|0|0|_
B= 1|1|0|1|0|_
Tin=1|_ S Tout in

{Subtrator5bits A B Tin S Tout}
{Browse inp(A B Tin)#sum(S Tout)}

%EPrimode5Bits
declare
   X=1|1|0|0|1|_ P
in
   {IsPrime5Bits X P}

%ESequenciade7Bits
declare
   Z = 1|0|1|0|1|0|1|_
   F
in
  {Sequencia_de_1_7bits Z F}