%Roberto Sergio Ribeiro de Meneses - 520403
%Guilherme Galvao Serra - 520402
functor
import  
   Portas at 'Funtor.ozf'
export
   subtrator:Subtrator
   eprimo:EPrimo4bitsE_Primo_5Bits
   sequencia_de_1:Sequencia_de_1_7bits
   
declare proc {Subtrator A B Tin ?S ?Tout}
	   K L M N
	in
	   S={Portas.xorg A {Portas.xorg B Tin}}
	   K={Portas.andg {Portas.notg A} B}
	   L={Portas.andg {Portas.notg A} Tin}
	   M={Portas.andg B Tin}
	   N={Portas.org K L}
	   Tout={Portas.org N M}
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
   proc {E_Primo_5Bits X ?R}
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

      And1 = {Portas.andg {Portas.notg K} {Portas.notg  L}}
      And2 = {Portas.andg And1 M}
      And3 = {Portas.andg {Portas.notg L} M}
      And4 = {Portas.andg And3 N}
      And5 = {Portas.andg {Portas.notg K} L}
      And6 = {Portas.andg And5 N}
      And7 = {Portas.andg {Portas.notg M} L}
      And8 = {Portas.andg And7 N}
      And9 = {Portas.andg {Portas.notg K} O}
      And10 = {Portas.andg And9 L}
      And11 = {Portas.andg And10 M}
      And12 = {Portas.andg And11 N}
      And13 = {Portas.andg {Portas.notg L} O}
      And14 = {Portas.andg And13 M}
      And15 = {Portas.andg And14 N}
      And16 = {Portas.andg {Portas.notg M} O}
      And17 = {Portas.andg And16 N}
      And18 = {Portas.andg {Portas.notg N} O}
      And19 = {Portas.andg {Portas.notg K} And3}
      And20 = {Portas.andg And19 O}
                        
      Or1 = {Portas.org And2 And4}
      Or2 = {Portas.org And6 And8}
      Or3 = {Portas.org And10 And11}
      Or4 = {Portas.org And12 And14}
      Or5 = {Portas.org And15 And17}
      Or6 = {Portas.org Or1 And20}
      Or7 = {Portas.org Or2 Or3}
      Or8 = {Portas.org Or4 Or5}
      Or9 = {Portas.org Or6 Or7}
						       
      R = {Portas.org Or8 Or9}
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
      
      And1 = {Portas.andg K L}
      And2 = {Portas.andg L M}
      And3 = {Portas.andg M N}
      And4 = {Portas.andg N O}
      And5 = {Portas.andg O P}
      And6 = {Portas.andg P Q}
      
      Or1 = {Portas.org And1 And2}
      Or2 = {Portas.org Or1 And3}
      Or3 = {Portas.org Or2 And4}
      Or4 = {Portas.org Or3 And5}
      
      R  = {Portas.org Or4 And6}

      case R
      of 1|_ then {Browse inp(X)#tem_1_em_sequencia}
      [] 0|_ then {Browse inp(X)#nao_tem_1_em_sequencia}
      end
      
   end