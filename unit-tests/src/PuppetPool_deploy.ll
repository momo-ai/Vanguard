; ModuleID = 'PuppetPool'
source_filename = "Pool.sol"
target datalayout = "e-m:e-p:32:32-i64:64-n32:64-S128-ni:1:10:20"
target triple = "wasm32-unknown-unknown-wasm"

%struct.vector.0 = type { i32, i32, [0 x i8] }
%struct.chunk.1 = type { %struct.chunk.1*, %struct.chunk.1*, i32, i32 }
%struct.vector = type { i32, i32, [0 x i8] }

@uint256_0 = hidden local_unnamed_addr constant i256 0, align 8
@uint256_1 = hidden local_unnamed_addr constant i256 1, align 8
@uint512_0 = hidden local_unnamed_addr constant i512 0, align 8
@uint512_1 = hidden local_unnamed_addr constant i512 1, align 8
@selector = internal global i32 0
@calldata_len = internal global i32 0
@calldata_data = internal global i8* null
@const_string = internal unnamed_addr constant [29 x i8] c"Address: insufficient balance"
@const_string.1 = internal unnamed_addr constant [58 x i8] c"Address: unable to send value, recipient may have reverted"
@keccak256_precompile = internal unnamed_addr constant [20 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\14"
@const_string.2 = internal unnamed_addr constant [31 x i8] c"ReentrancyGuard: reentrant call"
@const_string.3 = internal unnamed_addr constant [32 x i8] c"Not depositing enough collateral"
@keccak256_precompile.4 = internal unnamed_addr constant [20 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\14"
@keccak256_precompile.5 = internal unnamed_addr constant [20 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\14"
@const_string.6 = internal unnamed_addr constant [15 x i8] c"Transfer failed"
@runtime_code = internal unnamed_addr constant [13887 x i8] c"\00asm\01\00\00\00\01\98\01\11`\02\7F\7F\00`\01\7F\00`\05~\7F\7F\7F\7F\01\7F`\03\7F\7F\7F\00`\00\01\7F`\07\7F\7F\7F\7F\7F\7F\7F\00`\03\7F\7F\7F\01\7F`\01\7F\01\7F`\00\00`\04\7F\7F\7F\7F\00`\04\7F~~\7F\00`\04\7F\7F\7F\7F\01\7F`\02\7F\7F\01\7F`\18\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F~~~~\01\7F`\15\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\7F\01\7F`\04~~~~\01\7F`\05~~~~\7F\01\7F\02\BE\02\0E\08ethereum\06revert\00\00\08ethereum\0AgetAddress\00\01\08ethereum\12getExternalBalance\00\00\08ethereum\04call\00\02\08ethereum\0EreturnDataCopy\00\03\08ethereum\0BstorageLoad\00\00\08ethereum\0CstorageStore\00\00\08ethereum\11getReturnDataSize\00\04\08ethereum\0CgetCallValue\00\01\08ethereum\09getCaller\00\01\08ethereum\03log\00\05\08ethereum\0FgetCallDataSize\00\04\08ethereum\0CcallDataCopy\00\03\08ethereum\06finish\00\00\03\15\14\03\00\03\03\03\06\07\08\09\0A\0A\0B\0C\0D\0E\0F\0F\10\07\08\05\03\01\00\02\06\08\01\7F\01A\80\80\04\0B\07\11\02\06memory\02\00\04main\00!\0A\C8_\14\E6\01\01\02\7F\02@ \02E\0D\00 \02A\7Fj!\03\02@ \02A\07q\22\04E\0D\00\03@ \00 \01-\00\00:\00\00 \00A\01j!\00 \01A\01j!\01 \02A\7Fj!\02 \04A\7Fj\22\04\0D\00\0B\0B \03A\07I\0D\00\03@ \00 \01-\00\00:\00\00 \00A\01j \01A\01j-\00\00:\00\00 \00A\02j \01A\02j-\00\00:\00\00 \00A\03j \01A\03j-\00\00:\00\00 \00A\04j \01A\04j-\00\00:\00\00 \00A\05j \01A\05j-\00\00:\00\00 \00A\06j \01A\06j-\00\00:\00\00 \00A\07j \01A\07j-\00\00:\00\00 \00A\08j!\00 \01A\08j!\01 \02Axj\22\02\0D\00\0B\0B\0B\A9\01\01\02\7F\02@ \01E\0D\00 \01A\7Fj!\02\02@ \01A\07q\22\03E\0D\00\03@ \00B\007\03\00 \00A\08j!\00 \01A\7Fj!\01 \03A\7Fj\22\03\0D\00\0B\0B \02A\07I\0D\00\03@ \00B\007\03\00 \00A8jB\007\03\00 \00A0jB\007\03\00 \00A(jB\007\03\00 \00A jB\007\03\00 \00A\18jB\007\03\00 \00A\10jB\007\03\00 \00A\08jB\007\03\00 \00A\C0\00j!\00 \01Axj\22\01\0D\00\0B\0B\0B\A8\01\01\02\7F \02A\7Fj!\03 \00A\1Fj!\00\02@ \02A\03q\22\04E\0D\00\03@ \01 \00-\00\00:\00\00 \02A\7Fj!\02 \01A\01j!\01 \00A\7Fj!\00 \04A\7Fj\22\04\0D\00\0B\0B\02@ \03A\03I\0D\00\03@ \01 \00-\00\00:\00\00 \01A\01j \00A\7Fj-\00\00:\00\00 \01A\02j \00A~j-\00\00:\00\00 \01A\03j \00A}j-\00\00:\00\00 \01A\04j!\01 \00A|j!\00 \02A|j\22\02\0D\00\0B\0B\0B\A8\01\01\02\7F \02A\7Fj!\03 \01A\1Fj!\01\02@ \02A\03q\22\04E\0D\00\03@ \01 \00-\00\00:\00\00 \02A\7Fj!\02 \01A\7Fj!\01 \00A\01j!\00 \04A\7Fj\22\04\0D\00\0B\0B\02@ \03A\03I\0D\00\03@ \01 \00-\00\00:\00\00 \01A\7Fj \00A\01j-\00\00:\00\00 \01A~j \00A\02j-\00\00:\00\00 \01A}j \00A\03j-\00\00:\00\00 \01A|j!\01 \00A\04j!\00 \02A|j\22\02\0D\00\0B\0B\0B\AE\01\01\02\7F \02A\7Fj!\03\02@ \02A\03q\22\04E\0D\00\03@ \01 \02jA\7Fj \00-\00\00:\00\00 \02A\7Fj!\02 \00A\01j!\00 \04A\7Fj\22\04\0D\00\0B\0B \01 \02j!\04\02@ \03A\03I\0D\00 \04A|j!\04\03@ \04A\03j \00-\00\00:\00\00 \04A\02j \00A\01j-\00\00:\00\00 \04A\01j \00A\02j-\00\00:\00\00 \04 \00A\03j-\00\00:\00\00 \00A\04j!\00 \04A|j!\04 \02A|j\22\02\0D\00\0B\0B\0B\F0\02\01\03\7F \01 \00l\22\01A\08j\10\14\22\03 \006\02\04 \03 \006\02\00 \03A\08j!\00\02@\02@ \02A\7FF\0D\00 \01E\0D\01 \01A\7Fj!\04\02@ \01A\07q\22\05E\0D\00\03@ \00 \02-\00\00:\00\00 \00A\01j!\00 \02A\01j!\02 \01A\7Fj!\01 \05A\7Fj\22\05\0D\00\0B\0B \04A\07I\0D\01\03@ \00 \02-\00\00:\00\00 \00A\01j \02A\01j-\00\00:\00\00 \00A\02j \02A\02j-\00\00:\00\00 \00A\03j \02A\03j-\00\00:\00\00 \00A\04j \02A\04j-\00\00:\00\00 \00A\05j \02A\05j-\00\00:\00\00 \00A\06j \02A\06j-\00\00:\00\00 \00A\07j \02A\07j-\00\00:\00\00 \00A\08j!\00 \02A\08j!\02 \01Axj\22\01\0D\00\0C\02\0B\0B \01E\0D\00 \01A\7Fj!\05\02@ \01A\07q\22\02E\0D\00\03@ \00A\00:\00\00 \00A\01j!\00 \01A\7Fj!\01 \02A\7Fj\22\02\0D\00\0B\0B \05A\07I\0D\00\03@ \00B\007\00\00 \00A\08j!\00 \01Axj\22\01\0D\00\0B\0B \03\0B\A6\01\01\04\7FA\80\80\04!\01\02@\03@\02@ \01(\02\0C\0D\00 \01(\02\08\22\02 \00O\0D\02\0B \01(\02\00\22\01\0D\00\0BA\00!\01A\00(\02\08!\02\0B\02@ \02 \00A\07jAxq\22\03k\22\02A\18I\0D\00 \01 \03jA\10j\22\00 \01(\02\00\22\046\02\00\02@ \04E\0D\00 \04 \006\02\04\0B \00 \02Apj6\02\08 \00A\006\02\0C \00 \016\02\04 \01 \006\02\00 \01 \036\02\08\0B \01A\016\02\0C \01A\10j\0B.\00A\00A\006\02\80\80\04A\00A\006\02\84\80\04A\00A\006\02\8C\80\04A\00?\00A\10tA\F0\FF{j6\02\88\80\04\0B\85\03\04\07\7F\01~\03\7F\02~ \03A\1Fu \03q!\04 \03A\02t \00jA|j!\05 \03!\06\02@\03@\02@ \06A\01N\0D\00 \04!\07\0C\02\0B \06A\7Fj!\06 \05(\02\00!\08 \05A|j!\05 \08E\0D\00\0B \06A\01j!\07\0B \03A\02t \01jA|j!\05 \03!\06\02@\03@ \06A\01H\0D\01 \06A\7Fj!\06 \05(\02\00!\08 \05A|j!\05 \08E\0D\00\0B \06A\01j!\04\0B\02@ \03A\01H\0D\00 \01A|j!\09A\00!\0AB\00!\0BA\00!\0CA\00!\05A\00!\01\03@ \0A \04N!\0D\02@\02@ \05 \05 \04H\22\08j\22\0E \01 \0A \07Nj\22\01K\0D\00B\00!\0F \0B!\10\0C\01\0B \00 \0C \0DjA\02tj!\06 \09 \05 \08jA\02tj!\05B\00!\0F \0E!\08\03@ \0FB\80\80\80\80\10| \0F \0B \055\02\00 \065\02\00~|\22\10 \0BT\1B!\0F \06A\04j!\06 \05A|j!\05 \10!\0B \08A\7Fj\22\08 \01J\0D\00\0B\0B \0C \0Dj!\0C \02 \0AA\02tj \10>\02\00 \10B \88 \0F\84!\0B \0E!\05 \0AA\01j\22\0A \03G\0D\00\0B\0B\0BS\01\01~\02@ \03E\0D\00\02@ \03A\C0\00qE\0D\00 \01 \03A?q\AD\86!\02B\00!\01\0C\01\0B \01A\C0\00 \03k\AD\88 \02 \03\AD\22\04\86\84!\02 \01 \04\86!\01\0B \00 \027\03\08 \00 \017\03\00\0BS\01\01~\02@ \03E\0D\00\02@ \03A\C0\00qE\0D\00 \02 \03A?q\AD\88!\01B\00!\02\0C\01\0B \02A\C0\00 \03k\AD\86 \01 \03\AD\22\04\88\84!\01 \02 \04\88!\02\0B \00 \027\03\08 \00 \017\03\00\0B\8C\12\06\01\7F\0A~\02\7F\03~\01\7F\0D~#\00A\F0\00k\22\04$\00 \00A\18j)\03\00!\05 \00A\10j)\03\00!\06 \00A\08j)\03\00!\07 \00)\03\00!\08\02@\02@\02@ \01)\03\00\22\09B\01V \01A\08j)\03\00\22\0AB\00R \0AP\1B \01A\10j)\03\00\22\0BB\00R \01A\18j)\03\00\22\0CB\00R \0CP\1B \0B \0C\84P\1B\0D\00A\01!\00\02@ \09\A7\0E\02\03\00\03\0B \02B\007\03\10 \02B\007\03\08 \02B\007\03\00 \02A\18jB\007\03\00 \03 \067\03\10 \03 \087\03\00 \03 \077\03\08 \03A\18j \057\03\00\0C\01\0B\02@ \09 \08\85 \0B \06\85\22\0D\84 \0A \07\85 \0C \05\85\22\0E\84\84B\00R\0D\00 \02B\007\03\10 \02B\007\03\08 \02B\007\03\00 \02A\18jB\007\03\00 \03B\007\03\10 \03A\18jB\007\03\00 \03B\017\03\00 \03B\007\03\08\0C\01\0B\02@\02@ \08 \06\84 \07 \05\84\84P\0D\00 \08 \09Z \07 \0AZ \07 \0AQ\1B \06 \0BZ \05 \0CZ \05 \0CQ\1B \0D \0E\84P\1B\0D\01\0B \02 \087\03\00 \02 \077\03\08 \02 \067\03\10 \02A\18j \057\03\00 \03B\007\03\10 \03A\18jB\007\03\00 \03B\007\03\00 \03B\007\03\08\0C\01\0BA\C0\01!\00 \05!\0D\02@\02@ \05B\00R\0D\00A\80\01!\00 \06!\0D \06PE\0D\00A\C0\00!\00 \07!\0D \07B\00R\0D\00A\00!\00 \08!\0D \08B\00Q\0D\01\0BA\1FA? \0DB\80\80\80\80\10T\22\01\1B\22\0FApj \0F \0DB \86 \0D \01\1B\22\0DB\80\80\80\80\80\80\C0\00T\22\01\1B\22\0FAxj \0F \0DB\10\86 \0D \01\1B\22\0DB\80\80\80\80\80\80\80\80\01T\22\01\1B\22\0FA|j \0F \0DB\08\86 \0D \01\1B\22\0DB\80\80\80\80\80\80\80\80\10T\22\01\1B\22\0FA~j \0F \0DB\04\86 \0D \01\1B\22\0DB\80\80\80\80\80\80\80\80\C0\00T\22\01\1B \00j \0DB\02\86 \0D \01\1BB?\87\A7A\7Fsj!\00\0BA\C0\01!\01 \0C!\0D\02@\02@ \0CB\00R\0D\00A\80\01!\01 \0B!\0D \0BPE\0D\00A\C0\00!\01 \0A!\0D \0AB\00R\0D\00A\00!\01 \09!\0D \09B\00Q\0D\01\0BA\1FA? \0DB\80\80\80\80\10T\22\0F\1B\22\10Apj \10 \0DB \86 \0D \0F\1B\22\0DB\80\80\80\80\80\80\C0\00T\22\0F\1B\22\10Axj \10 \0DB\10\86 \0D \0F\1B\22\0DB\80\80\80\80\80\80\80\80\01T\22\0F\1B\22\10A|j \10 \0DB\08\86 \0D \0F\1B\22\0DB\80\80\80\80\80\80\80\80\10T\22\0F\1B\22\10A~j \10 \0DB\04\86 \0D \0F\1B\22\0DB\80\80\80\80\80\80\80\80\C0\00T\22\0F\1B \01j \0DB\02\86 \0D \0F\1BB?\87\A7A\7Fsj!\01\0B \04A0j \09 \0AA\80\01 \00 \01k\22\00k\10\18 \04A\E0\00j \0B \0C \00\10\17 \04A\C0\00j \09 \0A \00A\80\7Fj\10\17 \04A\D0\00j \09 \0A \00\10\17 \04A\E0\00jA\08j)\03\00 \04A0jA\08j)\03\00\84 \04A\C0\00jA\08j)\03\00 \00A\80\01I\22\0F\1B!\0E \04)\03` \04)\030\84 \04)\03@ \0F\1B!\11 \04A\D0\00jA\08j)\03\00!\12 \04)\03P!\13A\C0\01!\01 \05!\0D\02@\02@ \05B\00R\0D\00A\80\01!\01 \06!\0D \06PE\0D\00A\C0\00!\01 \07!\0D \07B\00R\0D\00A\00!\01 \08!\0D \08B\00Q\0D\01\0BA\1FA? \0DB\80\80\80\80\10T\22\10\1B\22\14Apj \14 \0DB \86 \0D \10\1B\22\0DB\80\80\80\80\80\80\C0\00T\22\10\1B\22\14Axj \14 \0DB\10\86 \0D \10\1B\22\0DB\80\80\80\80\80\80\80\80\01T\22\10\1B\22\14A|j \14 \0DB\08\86 \0D \10\1B\22\0DB\80\80\80\80\80\80\80\80\10T\22\10\1B\22\14A~j \14 \0DB\04\86 \0D \10\1B\22\0DB\80\80\80\80\80\80\80\80\C0\00T\22\10\1B \01j \0DB\02\86 \0D \10\1BB?\87\A7A\7Fsj!\01\0B \0E \0C \00\1B!\0D \11 \0B \00\1B!\11 \12B\00 \0F\1B!\15 \13B\00 \0F\1B!\12A\C0\01!\00 \0C!\0E\02@\02@ \0CB\00R\0D\00A\80\01!\00 \0B!\0E \0BPE\0D\00A\C0\00!\00 \0A!\0E \0AB\00R\0D\00A\00!\00 \09!\0E \09B\00Q\0D\01\0BA\1FA? \0EB\80\80\80\80\10T\22\0F\1B\22\10Apj \10 \0EB \86 \0E \0F\1B\22\0EB\80\80\80\80\80\80\C0\00T\22\0F\1B\22\10Axj \10 \0EB\10\86 \0E \0F\1B\22\0EB\80\80\80\80\80\80\80\80\01T\22\0F\1B\22\10A|j \10 \0EB\08\86 \0E \0F\1B\22\0EB\80\80\80\80\80\80\80\80\10T\22\0F\1B\22\10A~j \10 \0EB\04\86 \0E \0F\1B\22\0EB\80\80\80\80\80\80\80\80\C0\00T\22\0F\1B \00j \0EB\02\86 \0E \0F\1BB?\87\A7A\7Fsj!\00\0B \04A\10jB\01B\00 \01 \00k\22\00A\80\7Fj\10\17 \04B\01B\00A\80\01 \00k\10\18 \04A jB\01B\00 \00\10\17 \11 \12 \08V \15 \07V \15 \07Q\1B \11 \06V \0D \05V \0D \05Q\1B \11 \06\85 \0D \05\85\84P\1B\22\0F\AD\22\16\88 \0DB\01\86 \0FA?s\AD\22\17\86\84!\0E \12 \16\88 \15B\01\86 \17\86\84!\12 \04)\03\00 \04)\03\10 \00A\80\01I\22\01\1BB\00 \00\1B\22\18 \16\88 \04A\08j)\03\00 \04A\10jA\08j)\03\00 \01\1BB\00 \00\1B\22\19B\01\86 \17\86\84!\13 \04)\03 B\00 \01\1B \16\88 \04A jA\08j)\03\00B\00 \01\1B\22\1AB\01\86 \17\86\84!\1B \15 \16\88 \11B\01\86 \0FA\7FsA?q\AD\22\15\86\84!\11 \1A \16\88 \18B\01\86 \15\86\84!\15 \0D \16\88!\0D \19 \16\88!\16B\00!\1AB\00!\1CB\00!\1DB\00!\1E\03@B\00 \11 \08 \12T \07 \11T \07 \11Q\1B \06 \0ET \05 \0DT \05 \0DQ\1B \06 \0E\85 \05 \0D\85\84P\1B\22\00\1B!\17B\00 \12 \00\1B!\19B\00 \0D \00\1B!\1F \06B\00 \0E \00\1B\22\18T!\01B\00 \16 \00\1B \1E\84!\1EB\00 \13 \00\1B \1D\84!\1DB\00 \15 \00\1B \1C\84!\1CB\00 \1B \00\1B \1A\84!\1A \1BB\01\88 \15B?\86\84!\1B \12B\01\88 \11B?\86\84!\12 \15B\01\88 \13B?\86\84!\15 \11B\01\88 \0EB?\86\84!\11 \13B\01\88 \16B?\86\84!\13 \0EB\01\88 \0DB?\86\84!\0E \16B\01\88!\16 \0DB\01\88!\0D \06 \18}\22  \08 \19T\22\00 \07 \17T \07 \17Q\1B\AD\22!}\22\18!\06 \08 \19}\22\08 \09Z \07 \17} \00\AD}\22\07 \0AZ \07 \0AQ\1B \18 \0BZ \05 \1F} \01\AD}   !T\AD}\22\05 \0CZ \05 \0CQ\1B \18 \0B\85 \05 \0C\85\84P\1B\0D\00\0B \03 \1A7\03\00 \03 \1C7\03\08 \03 \1D7\03\10 \03A\18j \1E7\03\00 \02 \187\03\10 \02A\18j \057\03\00 \02 \087\03\00 \02 \077\03\08\0BA\00!\00\0B \04A\F0\00j$\00 \00\0B\A6\01\01\03\7F#\00A\10k\22\02$\00\02@ \00A\01qE\0D\00 \02A\10j$\00A\00\0F\0B \01(\02\00A\00 \01\1BA?jA`qA$j\22\03\10\14!\00 \02A\A0\F3\8D\C6\006\02\04 \02A\04j \00A\04\10\12 \00A\04j\22\04 \03A\03v\10\0F \02A 6\02\08 \02A\08j \04A\04\10\11 \02 \01(\02\00A\00 \01\1B\22\046\02\0C \02A\0Cj \00A$jA\04\10\11 \00A\C4\00j \01A\08j \04\10\0E \00 \03\10\00\00\0B\96\05\03\02\7F\01~\01\7F#\00A\D0\00k\22\18$\00 \18\22\19A$j\10\01 \19 \19)\00$7\00\10 \19 \19)\00,7\00\18 \19 \19(\0046\00  \19A\10j \19\10\02\02@\02@\02@ \19)\03\00 \14T \19A\08j)\03\00\22\1A \15T \1A \15Q\1B \1AB?\87\22\1A \16T \1A \17T \1A \17Q\1B \1A \16\85 \1A \17\85\84P\1B\0D\00A\00 \16B\00R \17B\00R \17P\1B \16 \17\84P\1B\0D\01 \18A`j\22\18\22\1B$\00 \18 \04:\00\04 \18 \03:\00\03 \18 \02:\00\02 \18 \01:\00\01 \18 \00:\00\00 \18 \05:\00\05 \18 \06:\00\06 \18 \07:\00\07 \18 \08:\00\08 \18 \09:\00\09 \18 \0A:\00\0A \18 \0B:\00\0B \18 \0C:\00\0C \18 \0D:\00\0D \18 \0E:\00\0E \18 \0F:\00\0F \18 \10:\00\10 \18 \11:\00\11 \18 \12:\00\12 \18 \13:\00\13 \1BApj\22\00$\00 \00 \157\03\08 \00 \147\03\00B\FF\FF\FF\FF\FF\FF\FF\FF\FF\00 \18 \00A\08A\00\10\03E\0D\02A:A\01A \10\13\22\00(\02\00A\00 \00\1BA?jA`qA$j\22\01\10\14!\18 \19A\A0\F3\8D\C6\006\02D \19A\C4\00j \18A\04\10\12 \18A\04j\22\02 \01A\03v\10\0F \19A 6\02H \19A\C8\00j \02A\04\10\11 \19 \00(\02\00A\00 \00\1B\22\026\02L \19A\CC\00j \18A$jA\04\10\11 \18A\C4\00j \00A\08j \02\10\0E \18 \01\10\00\00\0BA\1DA\01A\00\10\13\22\00(\02\00A\00 \00\1BA?jA`qA$j\22\01\10\14!\18 \19A\A0\F3\8D\C6\006\028 \19A8j \18A\04\10\12 \18A\04j\22\02 \01A\03v\10\0F \19A 6\02< \19A<j \02A\04\10\11 \19 \00(\02\00A\00 \00\1B\22\026\02@ \19A\C0\00j \18A$jA\04\10\11 \18A\C4\00j \00A\08j \02\10\0E \18 \01\10\00\00\0BA\00A\00\10\00\00\0B \19A\D0\00j$\00A\00\0B\BF\03\01\02\7F#\00A\F0\00k\22\15$\00 \15A@j\22\16$\00 \16A\18jB\007\03\00 \16B\007\03\10 \16B\007\03\08 \16B\017\03\00 \16A j \00:\00\00 \16A!j \01:\00\00 \16A\22j \02:\00\00 \16A#j \03:\00\00 \16A$j \04:\00\00 \16A%j \05:\00\00 \16A&j \06:\00\00 \16A'j \07:\00\00 \16A(j \08:\00\00 \16A)j \09:\00\00 \16A*j \0A:\00\00 \16A+j \0B:\00\00 \16A,j \0C:\00\00 \16A-j \0D:\00\00 \16A.j \0E:\00\00 \16A/j \0F:\00\00 \16A0j \10:\00\00 \16A1j \11:\00\00 \16A2j \12:\00\00 \16A3j \13:\00\00 \15\22\15B\007\03H \15B\007\03@B\FF\FF\FF\FF\FF\FF\FF\FF\FF\00A\A0\01 \15A\C0\00j \16A4\10\03\1A \15A\D0\00jA\00A \10\04 \15A jA\18j \15A\D0\00jA\18j)\03\007\03\00 \15 \15A\D0\00jA\10j)\03\007\030 \15 \15A\D0\00jA\08j)\03\007\03( \15 \15)\03P7\03  \15A j \15\10\05 \14A\18j \15A\18j)\03\007\03\00 \14 \15A\10j)\03\007\03\10 \14 \15A\08j)\03\007\03\08 \14 \15)\03\007\03\00 \15A\F0\00j$\00A\00\0B\F8\03\02\03\7F\04~#\00A\E0\00k\22\04$\00 \04\22\05A\C0\00jA\18jB\007\03\00 \05B\007\03P \05B\007\03H \05B\007\03@ \05A\C0\00j \05A j\10\05 \05A\18j\22\06 \05A jA\18j)\03\007\03\00 \05 \05A jA\10j)\03\007\03\10 \05 \05A jA\08j)\03\007\03\08 \05 \05)\03 7\03\00\02@\02@\02@\02@\02@\02@A\00\0D\00 \06)\03\00!\07 \05A\08j)\03\00!\08 \05)\03\00!\09 \05A\10j)\03\00!\0A \04Apj\22\04$\00 \04 \0A \09B\02\85\84 \08 \07\84\84B\00R:\00\00A\01E\0D\01 \04-\00\00A\1FA\01A\E0\00\10\13\10\1A\22\04\0D\02 \05A\C0\00jA\18jB\007\03\00 \05A jA\18jB\007\03\00 \05B\007\03P \05B\007\03H \05B\027\03@ \05B\007\030 \05B\007\03( \05B\007\03  \05A j \05A\C0\00j\10\06A\01E\0D\03 \00 \01 \02 \03\10\1E\22\04\0D\04 \05A\C0\00jA\18jB\007\03\00 \05A jA\18jB\007\03\00 \05B\007\03P \05B\007\03H \05B\017\03@ \05B\007\030 \05B\007\03( \05B\007\03  \05A j \05A\C0\00j\10\06A\01\0D\05 \05A\E0\00j$\00A\00\0F\0B \05A\E0\00j$\00A\00\0F\0B \05A\E0\00j$\00A\00\0F\0B \05A\E0\00j$\00 \04\0F\0B \05A\E0\00j$\00A\00\0F\0B \05A\E0\00j$\00 \04\0F\0B \05A\E0\00j$\00A\00\0B\CE\11\04\03\7F\05~\14\7F\07~#\00A\F0\01k\22\04$\00\02@\02@\02@\02@\02@\02@ \00 \01 \02 \03 \04\22\05A\08j\10\1F\22\06\0D\00 \05A\18j)\03\00!\07 \05A j)\03\00!\08 \05A\08jA\08j)\03\00!\09 \05)\03\08!\0A \04Apj\22\04\22\06$\00 \04\10\08 \04)\03\00 \0AZ \04A\08j)\03\00\22\0B \09Z \0B \09Q\1B \0BB?\87\22\0B \07Z \0B \08Z \0B \08Q\1B \0B \07\85 \0B \08\85\84P\1BE\0D\01 \06Apj\22\04\22\06$\00 \04\10\08\02@ \04)\03\00 \0AV \04A\08j)\03\00\22\0B \09V \0B \09Q\1B \0BB?\87\22\0B \07V \0B \08V \0B \08Q\1B \0B \07\85 \0B \08\85\84P\1BE\0D\00 \06A`j\22\04\22\06$\00 \04\10\09 \04-\00\13!\0C \04-\00\12!\0D \04-\00\11!\0E \04-\00\10!\0F \04-\00\0F!\10 \04-\00\0E!\11 \04-\00\0D!\12 \04-\00\0C!\13 \04-\00\0B!\14 \04-\00\0A!\15 \04-\00\09!\16 \04-\00\08!\17 \04-\00\07!\18 \04-\00\06!\19 \04-\00\05!\1A \04-\00\04!\1B \04-\00\03!\1C \04-\00\02!\1D \04-\00\01!\1E \04-\00\00!\1F \06Apj\22\04\22\06$\00 \04\10\08 \1F \1E \1D \1C \1B \1A \19 \18 \17 \16 \15 \14 \13 \12 \11 \10 \0F \0E \0D \0C \04)\03\00\22  \0A} \04A\08j)\03\00\22\0B \09}   \0AT\22\04\AD} \0BB?\87\22  \07}\22! \04 \0B \09T \0B \09Q\1B\AD\22\0B}   \08}   \07T\AD} ! \0BT\AD}\10\1B\22\04\0D\03\0B \06A`j\22\04\22\06$\00 \04\10\09 \04(\00\10!\0C \04)\00\08!\0B \04)\00\00!  \06A@j\22\04\22\06$\00 \04A\18jB\007\03\00 \04B\007\03\10 \04B\007\03\08 \04B\017\03\00 \04A j  7\00\00 \04A(j \0B7\00\00 \04A0j \0C6\00\00 \06A`j\22\06\22\0C$\00 \0CApj\22\0C\22\0D$\00 \0CB\007\03\08 \0CB\007\03\00B\FF\FF\FF\FF\FF\FF\FF\FF\FF\00A\A0\01 \0C \04A4\10\03\1A \06A\00A \10\04 \06)\03\00!\0B \06A\08j)\03\00!  \06A\10j)\03\00!! \06A\18j)\03\00!\22 \0DA`j\22\04\22\06$\00 \04A\18j \227\03\00 \04 !7\03\10 \04  7\03\08 \04 \0B7\03\00 \06A`j\22\06\22\0C$\00 \04 \06\10\05 \06A\18j)\03\00!# \06A\10j)\03\00!  \06A\08j)\03\00!\0B \06)\03\00!! \0CA`j\22\04\22\06$\00 \04\10\09 \04(\00\10!\0C \04)\00\08!\22 \04)\00\00!$ \06A@j\22\04\22\06$\00 \04A\18jB\007\03\00 \04B\007\03\10 \04B\007\03\08 \04B\017\03\00 \04A j $7\00\00 \04A(j \227\00\00 \04A0j \0C6\00\00 \06A`j\22\06\22\0C$\00 \0CApj\22\0C\22\0D$\00 \0CB\007\03\08 \0CB\007\03\00B\FF\FF\FF\FF\FF\FF\FF\FF\FF\00A\A0\01 \0C \04A4\10\03\1A \06A\00A \10\04 \06)\03\00!\22 \06A\08j)\03\00!$ \06A\10j)\03\00!% \06A\18j)\03\00!& \0DA`j\22\04\22\06$\00 \04A\18j &7\03\00 \04 %7\03\10 \04 $7\03\08 \04 \227\03\00 \05 ! \0A|\22\227\038 \05 \0B \09| \22 !T\22\0C\AD|\22!7\03@ \05   \07|\22\22 \0C ! \0BT ! \0BQ\1B\AD|\22\0B7\03H \05A8jA\18j # \08| \22  T\AD| \0B \22T\AD|7\03\00 \04 \05A8j\10\06 \06A`j\22\04\22\06$\00 \04A\18jB\007\03\00 \04B\007\03\10 \04B\007\03\08 \04B\037\03\00 \06A`j\22\06\22\0C$\00 \04 \06\10\05 \06)\00\00!\0B \06)\00\08!  \06(\00\10!\0D \0CA`j\22\04\22\06$\00 \04\10\09 \04)\00\00!! \04)\00\08!\22 \04(\00\10!\0CA\CC\00\10\14\22\04B\C4\80\80\80\C0\087\02\00 \05A\BB\B9\96\C8z6\02\\ \05A\DC\00j \04A\08j\22\0EA\04\10\12 \04A\0CjA\08\10\0F \05A\E0\00jA\18j \037\03\00 \04A(j \0C6\00\00 \04A j \227\00\00 \04A\18j !7\00\00 \05 \027\03p \05 \017\03h \05 \007\03` \05A\E0\00j \04A,jA \10\11 \06A`j\22\06\22\0C$\00 \06 \0D6\00\10 \06  7\00\08 \06 \0B7\00\00 \04(\02\00!\0D \0CApj\22\0C\22\0F$\00 \0CB\007\03\08 \0CB\007\03\00B\FF\FF\FF\FF\FF\FF\FF\FF\FF\00 \06 \0C \0E \0DA\00 \04\1B\10\03\0D\03\10\07\22\06A\08j\10\14\22\04 \066\02\00 \04A\04j \066\02\00 \04A\08j\22\0CA\00 \06\10\04 \04(\02\00A\00 \04\1BA\1FM\0D\04 \0CA\18j)\03\00B\00R\0D\05A\0FA\01A\B4\01\10\13\22\06(\02\00A\00 \06\1BA?jA`qA$j\22\0C\10\14!\04 \05A\A0\F3\8D\C6\006\02\E4\01 \05A\E4\01j \04A\04\10\12 \04A\04j\22\0D \0CA\03v\10\0F \05A 6\02\E8\01 \05A\E8\01j \0DA\04\10\11 \05 \06(\02\00A\00 \06\1B\22\0D6\02\EC\01 \05A\EC\01j \04A$jA\04\10\11 \04A\C4\00j \06A\08j \0D\10\0E \04 \0C\10\00\00\0B \05A\F0\01j$\00 \06\0F\0BA A\01A\80\01\10\13\22\06(\02\00A\00 \06\1BA?jA`qA$j\22\0C\10\14!\04 \05A\A0\F3\8D\C6\006\02, \05A,j \04A\04\10\12 \04A\04j\22\0D \0CA\03v\10\0F \05A 6\020 \05A0j \0DA\04\10\11 \05 \06(\02\00A\00 \06\1B\22\0D6\024 \05A4j \04A$jA\04\10\11 \04A\C4\00j \06A\08j \0D\10\0E \04 \0C\10\00\00\0B \05A\F0\01j$\00 \04\0F\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0B \0FA`j\22\04$\00 \04\10\09 \04)\00\00!\0B \04)\00\08!  \04(\00\10!\0CA\C0\00\10\14\22\06A\08\10\0F \05A\80\01jA\18j \087\03\00 \05 \077\03\90\01 \05 \097\03\88\01 \05 \0A7\03\80\01 \05A\80\01j \06A \10\11 \05A\A0\01jA\18j \037\03\00 \05 \027\03\B0\01 \05 \017\03\A8\01 \05 \007\03\A0\01 \05A\A0\01j \06A jA \10\11A\C0\00\10\14\22\04A\08\10\0F \05A\C0\01jA\18jB\8C\A8\F7\BF\C7\F7\F3\F4j7\03\00 \05B\86\AC\89\84\B6\ED\FC\CC\A8\7F7\03\D0\01 \05B\A0\84\AC\BC\81\BB\F2\95;7\03\C8\01 \05B\B0\CE\B5\BC\E1\A7\D4\D6w7\03\C0\01 \05A\C0\01j \04A \10\12 \04A<j \0C6\00\00 \04A4j  7\00\00 \04A,j \0B7\00\00 \06A\C0\00A\02 \04 \04A jA\00A\00\10\0A \05A\F0\01j$\00A\00\0B\9E\03\01\02\7F#\00A\80\02k\22\05$\00\02@\02@ \05\10 \22\06\0D\00 \05A\C0\00jA\18j \05A\18j)\03\007\03\00 \05A jA\18j \037\03\00 \05 \007\03  \05 \05)\03\007\03@ \05 \017\03( \05 \027\030 \05 \05A\10j)\03\007\03P \05 \05A\08j)\03\007\03H \05A j \05A\C0\00j \05A\E0\00jA\08\10\16 \05A\A0\01jA\18jB\007\03\00 \05A\80\01jA\18j \05A\E0\00jA\18j)\03\00B\01\86 \05A\E0\00jA\10j)\03\00\22\00B?\88\847\03\00 \05B\007\03\B0\01 \05B\007\03\A8\01 \05B\80\80\90\BB\BA\D6\AD\F0\0D7\03\A0\01 \05 \05)\03`\22\01B\01\867\03\80\01 \05 \00B\01\86 \05A\E0\00jA\08j)\03\00\22\00B?\88\847\03\90\01 \05 \00B\01\86 \01B?\88\847\03\88\01 \05A\80\01j \05A\A0\01j \05A\C0\01j \05A\E0\01j\10\19E\0D\01A\00A\00\10\00\00\0B \05A\80\02j$\00 \06\0F\0B \04 \05)\03\E0\017\03\00 \04A\18j \05A\E0\01jA\18j)\03\007\03\00 \04 \05A\E0\01jA\10j)\03\007\03\10 \04 \05A\E0\01jA\08j)\03\007\03\08 \05A\80\02j$\00A\00\0B\B2\0A\04\16\7F\02~\03\7F\04~#\00A\D0\03k\22\01$\00 \01\22\02A\88\01jA\18jB\007\03\00 \02B\007\03\98\01 \02B\007\03\90\01 \02B\027\03\88\01 \02A\88\01j \02A\E8\00j\10\05 \02-\00h!\03 \02-\00i!\04 \02-\00j!\05 \02-\00k!\06 \02-\00l!\07 \02-\00m!\08 \02-\00n!\09 \02-\00o!\0A \02-\00p!\0B \02-\00q!\0C \02-\00r!\0D \02-\00s!\0E \02-\00t!\0F \02-\00u!\10 \02-\00v!\11 \02-\00w!\12 \02-\00x!\13 \02-\00y!\14 \02-\00z!\15 \02-\00{!\16 \02A\C8\00jA\18jB\007\03\00 \02B\007\03X \02B\007\03P \02B\037\03H \02A\C8\00j \02A(j\10\05 \02)\00(!\17 \02)\000!\18 \02(\008!\19A,\10\14\22\1AB\A4\80\80\80\C0\047\02\00 \02A\B1\84\82\85\076\02\AC\03 \02A\AC\03j \1AA\08j\22\1BA\04\10\12 \1AA\0CjA\04\10\0F \1AA+j \16:\00\00 \1AA*j \15:\00\00 \1AA)j \14:\00\00 \1AA(j \13:\00\00 \1AA'j \12:\00\00 \1AA&j \11:\00\00 \1AA%j \10:\00\00 \1AA$j \0F:\00\00 \1AA#j \0E:\00\00 \1AA\22j \0D:\00\00 \1AA!j \0C:\00\00 \1AA j \0B:\00\00 \1AA\1Fj \0A:\00\00 \1AA\1Ej \09:\00\00 \1AA\1Dj \08:\00\00 \1AA\1Cj \07:\00\00 \1AA\1Bj \06:\00\00 \1AA\1Aj \05:\00\00 \1AA\19j \04:\00\00 \1AA\18j \03:\00\00 \02 \196\00\A8\03 \02 \187\00\A0\03 \02 \177\00\98\03 \1A(\02\00!\1A \02B\007\03\90\03 \02B\007\03\88\03\02@\02@\02@\02@B\FF\FF\FF\FF\FF\FF\FF\FF\FF\00 \02A\98\03j \02A\88\03j \1B \1A\10\03\0D\00\10\07\22\1AA\08j\10\14\22\19 \1A6\02\00 \19A\04j \1A6\02\00 \19A\08j\22\1BA\00 \1A\10\04 \19(\02\00A\1FM\0D\01 \1B \02A\B0\03jA \10\10 \02A\08jA\18j\22\1A \02A\B0\03jA\18j)\03\007\03\00 \02 \02A\B0\03jA\10j)\03\007\03\18 \02 \02A\B0\03jA\08j)\03\007\03\10 \02 \02)\03\B0\037\03\08A\00\0D\02 \02A\08jA\08j)\03\00!\17 \02A\08jA\10j)\03\00!\18 \1A)\03\00!\1C \02)\03\08!\1D \01A`j\22\1A\22\19$\00 \1A \0A:\00\07 \1A \09:\00\06 \1A \08:\00\05 \1A \07:\00\04 \1A \06:\00\03 \1A \05:\00\02 \1A \04:\00\01 \1A \03:\00\00 \1A \0B:\00\08 \1A \0C:\00\09 \1A \0D:\00\0A \1A \0E:\00\0B \1A \0F:\00\0C \1A \10:\00\0D \1A \11:\00\0E \1A \12:\00\0F \1A \13:\00\10 \1A \14:\00\11 \1A \15:\00\12 \1A \16:\00\13 \19Apj\22\19$\00 \1A \19\10\02 \02A\C8\01jA\18jB\007\03\00 \02A\A8\01jA\18j \19A\08j)\03\00\22\1EB?\87\22\1F7\03\00 \02B\007\03\D8\01 \02B\007\03\D0\01 \02B\80\80\90\BB\BA\D6\AD\F0\0D7\03\C8\01 \02 \1E7\03\B0\01 \02 \19)\03\007\03\A8\01 \02 \1F7\03\B8\01 \02A\A8\01j \02A\C8\01j \02A\E8\01jA\08\10\16 \02A\A8\02jA\18j \1C7\03\00 \02A\88\02jA\18j \02A\E8\01jA\18j)\03\007\03\00 \02 \187\03\B8\02 \02 \177\03\B0\02 \02 \1D7\03\A8\02 \02 \02A\E8\01jA\10j)\03\007\03\98\02 \02 \02A\E8\01jA\08j)\03\007\03\90\02 \02 \02)\03\E8\017\03\88\02 \02A\88\02j \02A\A8\02j \02A\C8\02j \02A\E8\02j\10\19E\0D\03A\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0B \02A\D0\03j$\00A\00\0F\0B \00 \02)\03\E8\027\03\00 \00A\18j \02A\E8\02jA\18j)\03\007\03\00 \00 \02A\F8\02j)\03\007\03\10 \00 \02A\F0\02j)\03\007\03\08 \02A\D0\03j$\00A\00\0B\89\10\02\06\7F\04~#\00A\80\03k\22\00!\01 \00$\00\10\15A\00\10\0B\22\026\02\C8\01A\00 \02\10\14\22\036\02\CC\01 \03A\00 \02\10\0C\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@\02@ \02A\03M\0D\00A\00 \03(\02\00\22\046\02\C4\01 \02A|j!\05 \03A\04j!\02\02@ \04A\C7\AD\90\DC\01J\0D\00\02@ \04A\AC\9C\D4\E8}J\0D\00 \04A\83\80\A9\94xF\0D\04 \04A\CF\ED\D4\C2{G\0D\02 \00Apj\22\03$\00 \03\10\08 \03)\03\00 \03A\08j)\03\00\84B\00R\0D\0B \05A\1FM\0D\0C \02 \01A(jA \10\10 \01A0j)\03\00!\06 \01A8j)\03\00!\07 \01)\03(!\08 \01A\E0\02jA\18j \01A(jA\18j)\03\007\03\00 \01A\C0\02jA\18jB\007\03\00 \01 \077\03\F0\02 \01 \067\03\E8\02 \01 \087\03\E0\02 \01B\007\03\D0\02 \01B\007\03\C8\02 \01B\007\03\C0\02 \01A\C0\02j \01A\E0\02j\10\06A\01\0D\0DA\00A\00\10\00\00\0B \04A\AD\9C\D4\E8}F\0D\02 \04A\C5\D7\AB\E7~G\0D\01 \05A I\0D\1E \02 \01A\E0\01jA \10\10 \01)\03\E0\01 \01A\E8\01j)\03\00 \01A\F0\01j)\03\00 \01A\F8\01j)\03\00\10\1DE\0D\1FA\00A\00\10\00\00\0B\02@ \04A\F3\83\F4\E6\04J\0D\00 \04A\C8\AD\90\DC\01F\0D\06 \04A\BC\AB\B1\C2\02G\0D\01 \00Apj\22\03$\00 \03\10\08 \03)\03\00 \03A\08j)\03\00\84B\00R\0D  \05A\1FM\0D! \02 \01A\80\02jA \10\10 \01)\03\80\02 \01A\88\02j)\03\00 \01A\90\02j)\03\00 \01A\98\02j)\03\00 \01A\A0\02j\10\1FE\0D\22A\00A\00\10\00\00\0B \04A\F4\83\F4\E6\04F\0D\03 \04A\FC\99\D0\D2\06F\0D\06 \04A\FC\FD\A1\E9\06F\0D\04\0BA\00A\00\10\00\00\0B \00Apj\22\02$\00 \02\10\08 \02)\03\00 \02A\08j)\03\00\84B\00R\0D\05 \01A\E0\02jA\18jB\007\03\00 \01B\007\03\F0\02 \01B\007\03\E8\02 \01B\007\03\E0\02 \01A\E0\02j \01A\C0\02j\10\05 \01A\08jA\18j \01A\C0\02jA\18j)\03\007\03\00 \01 \01A\D0\02j)\03\007\03\18 \01 \01A\C0\02jA\08j)\03\007\03\10 \01 \01)\03\C0\027\03\08A\01\0D\06A\00A\00\10\00\00\0B \00Apj\22\03$\00 \03\10\08 \03)\03\00 \03A\08j)\03\00\84B\00R\0D\09 \05A\1FM\0D\0A \02 \01A\C8\00jA \10\10 \05\ADB?X\0D\0B \01A\C8\00jA\18j)\03\00!\06 \01A\C8\00jA\10j)\03\00!\07 \01A\C8\00jA\08j)\03\00!\08 \01)\03H!\09 \02A j \01A\E8\00jA \10\10 \01 \09 \01)\03h\85 \07 \01A\E8\00jA\10j)\03\00\85\84 \08 \01A\E8\00jA\08j)\03\00\85 \06 \01A\E8\00jA\18j)\03\00\85\84\84B\00R:\00\8F\01A\01\0D\0CA\00A\00\10\00\00\0B \00Apj\22\03$\00 \03\10\08 \03)\03\00 \03A\08j)\03\00\84B\00R\0D\0C \05A\1FM\0D\0D \05\AD\22\06B?X\0D\0E \02A\18j)\03\00!\09 \02A j \01A\90\01jA\04\10\10 \015\02\90\01\22\08B |\22\07 \06V\0D\0F \02 \08\A7j \01A\94\01jA\04\10\10 \07 \015\02\94\01\22\08| \06V\0D\10 \09B\00R \08\A7A\01 \02 \07\A7j\10\13\10\1AE\0D\11A\00A\00\10\00\00\0B \00Apj\22\03$\00 \03\10\08 \03)\03\00 \03A\08j)\03\00\84B\00R\0D\11 \05A\1FM\0D\12 \02A\0Cj-\00\00 \02A\0Dj-\00\00 \02A\0Ej-\00\00 \02A\0Fj-\00\00 \02A\10j-\00\00 \02A\11j-\00\00 \02A\12j-\00\00 \02A\13j-\00\00 \02A\14j-\00\00 \02A\15j-\00\00 \02A\16j-\00\00 \02A\17j-\00\00 \02A\18j-\00\00 \02A\19j-\00\00 \02A\1Aj-\00\00 \02A\1Bj-\00\00 \02A\1Cj-\00\00 \02A\1Dj-\00\00 \02A\1Ej-\00\00 \02A\1Fj-\00\00 \01A\98\01j\10\1CE\0D\13A\00A\00\10\00\00\0B \00Apj\22\02$\00 \02\10\08 \02)\03\00 \02A\08j)\03\00\84B\00R\0D\13 \01A\F8\02jB\007\03\00 \01B\007\03\F0\02 \01B\007\03\E8\02 \01B\027\03\E0\02 \01A\E0\02j \01A\C0\02j\10\05 \01 \01)\00\C0\027\00\B8\01 \01 \01)\00\C8\027\00\C0\01 \01 \01(\00\D0\026\00\C8\01A\01\0D\14A\00A\00\10\00\00\0B \00Apj\22\02$\00 \02\10\08 \02)\03\00 \02A\08j)\03\00\84B\00R\0D\14 \01A\F8\02jB\007\03\00 \01B\007\03\F0\02 \01B\007\03\E8\02 \01B\037\03\E0\02 \01A\E0\02j \01A\C0\02j\10\05 \01 \01)\00\C0\027\00\CC\01 \01 \01)\00\C8\027\00\D4\01 \01 \01(\00\D0\026\00\DC\01A\01\0D\15A\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA \10\14\22\02A\04\10\0F \01A\08j \02A \10\11 \02A \10\0D\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\0D\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA \10\14\22\02A\04\10\0F \02A\1Fj \01-\00\8F\01:\00\00 \02A \10\0D\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA\00A\00\10\0D\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA \10\14\22\02A\04\10\0F \01A\98\01j \02A \10\11 \02A \10\0D\00\0BA\00A\00\10\00\00\0BA \10\14\22\02A\04\10\0F \02A\0Cj \01)\00\B8\017\00\00 \02A\14j \01)\00\C0\017\00\00 \02A\1Cj \01(\00\C8\016\00\00 \02A \10\0D\00\0BA\00A\00\10\00\00\0BA \10\14\22\02A\04\10\0F \02A\0Cj \01)\00\CC\017\00\00 \02A\14j \01)\00\D4\017\00\00 \02A\1Cj \01(\00\DC\016\00\00 \02A \10\0D\00\0BA\00A\00\10\00\00\0BA\00A\00\10\0D\00\0BA\00A\00\10\00\00\0BA\00A\00\10\00\00\0BA \10\14\22\02A\04\10\0F \01A\A0\02j \02A \10\11 \02A \10\0D\00\0B\0B\CA\01\01\00A\00\0B\C3\01Address: insufficient balance\00\00\00Address: unable to send value, recipient may have reverted\00\00\00\00\00\00ReentrancyGuard: reentrant call\00Not depositing enough collateral\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\14Transfer failed\00}\09producers\01\0Cprocessed-by\01\05clang]13.0.0 (https://github.com/solana-labs/llvm-project 9743d18ce86564710488a1cd6438f09e95f17b3f)\00\88\06\04name\01\E0\05\22\00\06revert\01\0AgetAddress\02\12getExternalBalance\03\04call\04\0EreturnDataCopy\05\0BstorageLoad\06\0CstorageStore\07\11getReturnDataSize\08\0CgetCallValue\09\09getCaller\0A\03log\0B\0FgetCallDataSize\0C\0CcallDataCopy\0D\06finish\0E\08__memcpy\0F\08__bzero8\10\0B__be32toleN\11\0B__leNtobe32\12\0A__leNtobeN\13\0Avector_new\14\08__malloc\15\0B__init_heap\16\07__mul32\17\09__ashlti3\18\09__lshrti3\19\0Audivmod256\1A=PuppetPool::ReentrancyGuard::function::v_require__bool_string\1B9PuppetPool::Address::function::sendValue__address_uint256\1C3PuppetPool::PuppetPool::function::deposits__address\1D@PuppetPool::PuppetPool::borrow__uint256::modifier0::nonReentrant\1E1PuppetPool::PuppetPool::function::borrow__uint256\1FCPuppetPool::PuppetPool::function::calculateDepositRequired__uint256 5PuppetPool::PuppetPool::function::_computeOraclePrice!\04main\07\12\01\00\0F__stack_pointer\09\0A\01\00\07.rodata"

; Function Attrs: nofree norecurse nosync nounwind writeonly
define hidden void @__memset8(i8* nocapture %_dest, i64 %val, i32 %length) local_unnamed_addr #0 {
entry:
  %0 = bitcast i8* %_dest to i64*
  %1 = add i32 %length, -1
  %xtraiter = and i32 %length, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %dest.0.prol = phi i64* [ %incdec.ptr.prol, %do.body.prol ], [ %0, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i64, i64* %dest.0.prol, i32 1
  store i64 %val, i64* %dest.0.prol, align 8, !tbaa !4
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !8

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %dest.0.unr = phi i64* [ %0, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %2 = icmp ult i32 %1, 7
  br i1 %2, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %length.addr.0 = phi i32 [ %dec.7, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %dest.0 = phi i64* [ %incdec.ptr.7, %do.body ], [ %dest.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i64, i64* %dest.0, i32 1
  store i64 %val, i64* %dest.0, align 8, !tbaa !4
  %incdec.ptr.1 = getelementptr inbounds i64, i64* %dest.0, i32 2
  store i64 %val, i64* %incdec.ptr, align 8, !tbaa !4
  %incdec.ptr.2 = getelementptr inbounds i64, i64* %dest.0, i32 3
  store i64 %val, i64* %incdec.ptr.1, align 8, !tbaa !4
  %incdec.ptr.3 = getelementptr inbounds i64, i64* %dest.0, i32 4
  store i64 %val, i64* %incdec.ptr.2, align 8, !tbaa !4
  %incdec.ptr.4 = getelementptr inbounds i64, i64* %dest.0, i32 5
  store i64 %val, i64* %incdec.ptr.3, align 8, !tbaa !4
  %incdec.ptr.5 = getelementptr inbounds i64, i64* %dest.0, i32 6
  store i64 %val, i64* %incdec.ptr.4, align 8, !tbaa !4
  %incdec.ptr.6 = getelementptr inbounds i64, i64* %dest.0, i32 7
  store i64 %val, i64* %incdec.ptr.5, align 8, !tbaa !4
  %incdec.ptr.7 = getelementptr inbounds i64, i64* %dest.0, i32 8
  store i64 %val, i64* %incdec.ptr.6, align 8, !tbaa !4
  %dec.7 = add i32 %length.addr.0, -8
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %do.end, label %do.body, !llvm.loop !10

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind writeonly
define hidden void @__memset(i8* nocapture %_dest, i8 zeroext %val, i32 %length) local_unnamed_addr #0 {
entry:
  %0 = add i32 %length, -1
  %xtraiter = and i32 %length, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %dest.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %_dest, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %dest.0.prol, i32 1
  store i8 %val, i8* %dest.0.prol, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !13

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %dest.0.unr = phi i8* [ %_dest, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %1 = icmp ult i32 %0, 7
  br i1 %1, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %length.addr.0 = phi i32 [ %dec.7, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %dest.0 = phi i8* [ %incdec.ptr.7, %do.body ], [ %dest.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %dest.0, i32 1
  store i8 %val, i8* %dest.0, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %dest.0, i32 2
  store i8 %val, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %dest.0, i32 3
  store i8 %val, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %dest.0, i32 4
  store i8 %val, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr.4 = getelementptr inbounds i8, i8* %dest.0, i32 5
  store i8 %val, i8* %incdec.ptr.3, align 1, !tbaa !12
  %incdec.ptr.5 = getelementptr inbounds i8, i8* %dest.0, i32 6
  store i8 %val, i8* %incdec.ptr.4, align 1, !tbaa !12
  %incdec.ptr.6 = getelementptr inbounds i8, i8* %dest.0, i32 7
  store i8 %val, i8* %incdec.ptr.5, align 1, !tbaa !12
  %incdec.ptr.7 = getelementptr inbounds i8, i8* %dest.0, i32 8
  store i8 %val, i8* %incdec.ptr.6, align 1, !tbaa !12
  %dec.7 = add i32 %length.addr.0, -8
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %do.end, label %do.body, !llvm.loop !14

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind
define hidden void @__memcpy8(i8* nocapture %_dest, i8* nocapture readonly %_src, i32 %length) local_unnamed_addr #1 {
entry:
  %0 = bitcast i8* %_dest to i64*
  %1 = bitcast i8* %_src to i64*
  %2 = add i32 %length, -1
  %xtraiter = and i32 %length, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %dest.0.prol = phi i64* [ %incdec.ptr1.prol, %do.body.prol ], [ %0, %entry ]
  %src.0.prol = phi i64* [ %incdec.ptr.prol, %do.body.prol ], [ %1, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i64, i64* %src.0.prol, i32 1
  %3 = load i64, i64* %src.0.prol, align 8, !tbaa !4
  %incdec.ptr1.prol = getelementptr inbounds i64, i64* %dest.0.prol, i32 1
  store i64 %3, i64* %dest.0.prol, align 8, !tbaa !4
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !15

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %dest.0.unr = phi i64* [ %0, %entry ], [ %incdec.ptr1.prol, %do.body.prol ]
  %src.0.unr = phi i64* [ %1, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %4 = icmp ult i32 %2, 7
  br i1 %4, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %length.addr.0 = phi i32 [ %dec.7, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %dest.0 = phi i64* [ %incdec.ptr1.7, %do.body ], [ %dest.0.unr, %do.body.prol.loopexit ]
  %src.0 = phi i64* [ %incdec.ptr.7, %do.body ], [ %src.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i64, i64* %src.0, i32 1
  %5 = load i64, i64* %src.0, align 8, !tbaa !4
  %incdec.ptr1 = getelementptr inbounds i64, i64* %dest.0, i32 1
  store i64 %5, i64* %dest.0, align 8, !tbaa !4
  %incdec.ptr.1 = getelementptr inbounds i64, i64* %src.0, i32 2
  %6 = load i64, i64* %incdec.ptr, align 8, !tbaa !4
  %incdec.ptr1.1 = getelementptr inbounds i64, i64* %dest.0, i32 2
  store i64 %6, i64* %incdec.ptr1, align 8, !tbaa !4
  %incdec.ptr.2 = getelementptr inbounds i64, i64* %src.0, i32 3
  %7 = load i64, i64* %incdec.ptr.1, align 8, !tbaa !4
  %incdec.ptr1.2 = getelementptr inbounds i64, i64* %dest.0, i32 3
  store i64 %7, i64* %incdec.ptr1.1, align 8, !tbaa !4
  %incdec.ptr.3 = getelementptr inbounds i64, i64* %src.0, i32 4
  %8 = load i64, i64* %incdec.ptr.2, align 8, !tbaa !4
  %incdec.ptr1.3 = getelementptr inbounds i64, i64* %dest.0, i32 4
  store i64 %8, i64* %incdec.ptr1.2, align 8, !tbaa !4
  %incdec.ptr.4 = getelementptr inbounds i64, i64* %src.0, i32 5
  %9 = load i64, i64* %incdec.ptr.3, align 8, !tbaa !4
  %incdec.ptr1.4 = getelementptr inbounds i64, i64* %dest.0, i32 5
  store i64 %9, i64* %incdec.ptr1.3, align 8, !tbaa !4
  %incdec.ptr.5 = getelementptr inbounds i64, i64* %src.0, i32 6
  %10 = load i64, i64* %incdec.ptr.4, align 8, !tbaa !4
  %incdec.ptr1.5 = getelementptr inbounds i64, i64* %dest.0, i32 6
  store i64 %10, i64* %incdec.ptr1.4, align 8, !tbaa !4
  %incdec.ptr.6 = getelementptr inbounds i64, i64* %src.0, i32 7
  %11 = load i64, i64* %incdec.ptr.5, align 8, !tbaa !4
  %incdec.ptr1.6 = getelementptr inbounds i64, i64* %dest.0, i32 7
  store i64 %11, i64* %incdec.ptr1.5, align 8, !tbaa !4
  %incdec.ptr.7 = getelementptr inbounds i64, i64* %src.0, i32 8
  %12 = load i64, i64* %incdec.ptr.6, align 8, !tbaa !4
  %incdec.ptr1.7 = getelementptr inbounds i64, i64* %dest.0, i32 8
  store i64 %12, i64* %incdec.ptr1.6, align 8, !tbaa !4
  %dec.7 = add i32 %length.addr.0, -8
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %do.end, label %do.body, !llvm.loop !16

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind
define hidden void @__memcpy(i8* nocapture %_dest, i8* nocapture readonly %_src, i32 %length) local_unnamed_addr #1 {
entry:
  %tobool.not4 = icmp eq i32 %length, 0
  br i1 %tobool.not4, label %while.end, label %while.body.preheader

while.body.preheader:                             ; preds = %entry
  %0 = add i32 %length, -1
  %xtraiter = and i32 %length, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol

while.body.prol:                                  ; preds = %while.body.preheader, %while.body.prol
  %src.07.prol = phi i8* [ %incdec.ptr.prol, %while.body.prol ], [ %_src, %while.body.preheader ]
  %dest.06.prol = phi i8* [ %incdec.ptr1.prol, %while.body.prol ], [ %_dest, %while.body.preheader ]
  %length.addr.05.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %length, %while.body.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.preheader ]
  %dec.prol = add i32 %length.addr.05.prol, -1
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %src.07.prol, i32 1
  %1 = load i8, i8* %src.07.prol, align 1, !tbaa !12
  %incdec.ptr1.prol = getelementptr inbounds i8, i8* %dest.06.prol, i32 1
  store i8 %1, i8* %dest.06.prol, align 1, !tbaa !12
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %while.body.prol.loopexit, label %while.body.prol, !llvm.loop !17

while.body.prol.loopexit:                         ; preds = %while.body.prol, %while.body.preheader
  %src.07.unr = phi i8* [ %_src, %while.body.preheader ], [ %incdec.ptr.prol, %while.body.prol ]
  %dest.06.unr = phi i8* [ %_dest, %while.body.preheader ], [ %incdec.ptr1.prol, %while.body.prol ]
  %length.addr.05.unr = phi i32 [ %length, %while.body.preheader ], [ %dec.prol, %while.body.prol ]
  %2 = icmp ult i32 %0, 7
  br i1 %2, label %while.end, label %while.body

while.body:                                       ; preds = %while.body.prol.loopexit, %while.body
  %src.07 = phi i8* [ %incdec.ptr.7, %while.body ], [ %src.07.unr, %while.body.prol.loopexit ]
  %dest.06 = phi i8* [ %incdec.ptr1.7, %while.body ], [ %dest.06.unr, %while.body.prol.loopexit ]
  %length.addr.05 = phi i32 [ %dec.7, %while.body ], [ %length.addr.05.unr, %while.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %src.07, i32 1
  %3 = load i8, i8* %src.07, align 1, !tbaa !12
  %incdec.ptr1 = getelementptr inbounds i8, i8* %dest.06, i32 1
  store i8 %3, i8* %dest.06, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %src.07, i32 2
  %4 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr1.1 = getelementptr inbounds i8, i8* %dest.06, i32 2
  store i8 %4, i8* %incdec.ptr1, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %src.07, i32 3
  %5 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr1.2 = getelementptr inbounds i8, i8* %dest.06, i32 3
  store i8 %5, i8* %incdec.ptr1.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %src.07, i32 4
  %6 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr1.3 = getelementptr inbounds i8, i8* %dest.06, i32 4
  store i8 %6, i8* %incdec.ptr1.2, align 1, !tbaa !12
  %incdec.ptr.4 = getelementptr inbounds i8, i8* %src.07, i32 5
  %7 = load i8, i8* %incdec.ptr.3, align 1, !tbaa !12
  %incdec.ptr1.4 = getelementptr inbounds i8, i8* %dest.06, i32 5
  store i8 %7, i8* %incdec.ptr1.3, align 1, !tbaa !12
  %incdec.ptr.5 = getelementptr inbounds i8, i8* %src.07, i32 6
  %8 = load i8, i8* %incdec.ptr.4, align 1, !tbaa !12
  %incdec.ptr1.5 = getelementptr inbounds i8, i8* %dest.06, i32 6
  store i8 %8, i8* %incdec.ptr1.4, align 1, !tbaa !12
  %incdec.ptr.6 = getelementptr inbounds i8, i8* %src.07, i32 7
  %9 = load i8, i8* %incdec.ptr.5, align 1, !tbaa !12
  %incdec.ptr1.6 = getelementptr inbounds i8, i8* %dest.06, i32 7
  store i8 %9, i8* %incdec.ptr1.5, align 1, !tbaa !12
  %dec.7 = add i32 %length.addr.05, -8
  %incdec.ptr.7 = getelementptr inbounds i8, i8* %src.07, i32 8
  %10 = load i8, i8* %incdec.ptr.6, align 1, !tbaa !12
  %incdec.ptr1.7 = getelementptr inbounds i8, i8* %dest.06, i32 8
  store i8 %10, i8* %incdec.ptr1.6, align 1, !tbaa !12
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %while.end, label %while.body, !llvm.loop !18

while.end:                                        ; preds = %while.body.prol.loopexit, %while.body, %entry
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind writeonly
define hidden void @__bzero8(i8* nocapture %_dest, i32 %length) local_unnamed_addr #0 {
entry:
  %tobool.not2 = icmp eq i32 %length, 0
  br i1 %tobool.not2, label %while.end, label %while.body.preheader

while.body.preheader:                             ; preds = %entry
  %0 = bitcast i8* %_dest to i64*
  %1 = add i32 %length, -1
  %xtraiter = and i32 %length, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol

while.body.prol:                                  ; preds = %while.body.preheader, %while.body.prol
  %dest.04.prol = phi i64* [ %incdec.ptr.prol, %while.body.prol ], [ %0, %while.body.preheader ]
  %length.addr.03.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %length, %while.body.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.preheader ]
  %dec.prol = add i32 %length.addr.03.prol, -1
  %incdec.ptr.prol = getelementptr inbounds i64, i64* %dest.04.prol, i32 1
  store i64 0, i64* %dest.04.prol, align 8, !tbaa !4
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %while.body.prol.loopexit, label %while.body.prol, !llvm.loop !19

while.body.prol.loopexit:                         ; preds = %while.body.prol, %while.body.preheader
  %dest.04.unr = phi i64* [ %0, %while.body.preheader ], [ %incdec.ptr.prol, %while.body.prol ]
  %length.addr.03.unr = phi i32 [ %length, %while.body.preheader ], [ %dec.prol, %while.body.prol ]
  %2 = icmp ult i32 %1, 7
  br i1 %2, label %while.end, label %while.body

while.body:                                       ; preds = %while.body.prol.loopexit, %while.body
  %dest.04 = phi i64* [ %incdec.ptr.7, %while.body ], [ %dest.04.unr, %while.body.prol.loopexit ]
  %length.addr.03 = phi i32 [ %dec.7, %while.body ], [ %length.addr.03.unr, %while.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i64, i64* %dest.04, i32 1
  store i64 0, i64* %dest.04, align 8, !tbaa !4
  %incdec.ptr.1 = getelementptr inbounds i64, i64* %dest.04, i32 2
  store i64 0, i64* %incdec.ptr, align 8, !tbaa !4
  %incdec.ptr.2 = getelementptr inbounds i64, i64* %dest.04, i32 3
  store i64 0, i64* %incdec.ptr.1, align 8, !tbaa !4
  %incdec.ptr.3 = getelementptr inbounds i64, i64* %dest.04, i32 4
  store i64 0, i64* %incdec.ptr.2, align 8, !tbaa !4
  %incdec.ptr.4 = getelementptr inbounds i64, i64* %dest.04, i32 5
  store i64 0, i64* %incdec.ptr.3, align 8, !tbaa !4
  %incdec.ptr.5 = getelementptr inbounds i64, i64* %dest.04, i32 6
  store i64 0, i64* %incdec.ptr.4, align 8, !tbaa !4
  %incdec.ptr.6 = getelementptr inbounds i64, i64* %dest.04, i32 7
  store i64 0, i64* %incdec.ptr.5, align 8, !tbaa !4
  %dec.7 = add i32 %length.addr.03, -8
  %incdec.ptr.7 = getelementptr inbounds i64, i64* %dest.04, i32 8
  store i64 0, i64* %incdec.ptr.6, align 8, !tbaa !4
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %while.end, label %while.body, !llvm.loop !20

while.end:                                        ; preds = %while.body.prol.loopexit, %while.body, %entry
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind readonly
define hidden i32 @__memcmp_ord(i8* nocapture readonly %a, i8* nocapture readonly %b, i32 %len) local_unnamed_addr #2 {
entry:
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %a.addr.0 = phi i8* [ %a, %entry ], [ %incdec.ptr, %do.cond ]
  %b.addr.0 = phi i8* [ %b, %entry ], [ %incdec.ptr1, %do.cond ]
  %len.addr.0 = phi i32 [ %len, %entry ], [ %dec, %do.cond ]
  %0 = load i8, i8* %a.addr.0, align 1, !tbaa !12
  %conv = zext i8 %0 to i32
  %1 = load i8, i8* %b.addr.0, align 1, !tbaa !12
  %conv2 = zext i8 %1 to i32
  %sub = sub nsw i32 %conv, %conv2
  %tobool.not = icmp eq i32 %sub, 0
  br i1 %tobool.not, label %do.cond, label %return

do.cond:                                          ; preds = %do.body
  %incdec.ptr1 = getelementptr inbounds i8, i8* %b.addr.0, i32 1
  %incdec.ptr = getelementptr inbounds i8, i8* %a.addr.0, i32 1
  %dec = add i32 %len.addr.0, -1
  %tobool3.not = icmp eq i32 %dec, 0
  br i1 %tobool3.not, label %return, label %do.body, !llvm.loop !21

return:                                           ; preds = %do.cond, %do.body
  ret i32 %sub
}

; Function Attrs: nofree norecurse nosync nounwind
define hidden void @__be32toleN(i8* nocapture readonly %from, i8* nocapture %to, i32 %length) local_unnamed_addr #1 {
entry:
  %add.ptr = getelementptr inbounds i8, i8* %from, i32 31
  %0 = add i32 %length, -1
  %xtraiter = and i32 %length, 3
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %add.ptr, %entry ]
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %to, %entry ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %from.addr.0.prol, i32 -1
  %1 = load i8, i8* %from.addr.0.prol, align 1, !tbaa !12
  %incdec.ptr1.prol = getelementptr inbounds i8, i8* %to.addr.0.prol, i32 1
  store i8 %1, i8* %to.addr.0.prol, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !22

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %from.addr.0.unr = phi i8* [ %add.ptr, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %to.addr.0.unr = phi i8* [ %to, %entry ], [ %incdec.ptr1.prol, %do.body.prol ]
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %2 = icmp ult i32 %0, 3
  br i1 %2, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %from.addr.0 = phi i8* [ %incdec.ptr.3, %do.body ], [ %from.addr.0.unr, %do.body.prol.loopexit ]
  %to.addr.0 = phi i8* [ %incdec.ptr1.3, %do.body ], [ %to.addr.0.unr, %do.body.prol.loopexit ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %from.addr.0, i32 -1
  %3 = load i8, i8* %from.addr.0, align 1, !tbaa !12
  %incdec.ptr1 = getelementptr inbounds i8, i8* %to.addr.0, i32 1
  store i8 %3, i8* %to.addr.0, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %from.addr.0, i32 -2
  %4 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr1.1 = getelementptr inbounds i8, i8* %to.addr.0, i32 2
  store i8 %4, i8* %incdec.ptr1, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %from.addr.0, i32 -3
  %5 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr1.2 = getelementptr inbounds i8, i8* %to.addr.0, i32 3
  store i8 %5, i8* %incdec.ptr1.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %from.addr.0, i32 -4
  %6 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr1.3 = getelementptr inbounds i8, i8* %to.addr.0, i32 4
  store i8 %6, i8* %incdec.ptr1.2, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  br i1 %tobool.not.3, label %do.end, label %do.body, !llvm.loop !23

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind
define hidden void @__beNtoleN(i8* nocapture readonly %from, i8* nocapture %to, i32 %length) local_unnamed_addr #1 {
entry:
  %add.ptr = getelementptr inbounds i8, i8* %from, i32 %length
  %0 = add i32 %length, -1
  %xtraiter = and i32 %length, 3
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %add.ptr, %entry ]
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %to, %entry ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %from.addr.0.prol, i32 -1
  %1 = load i8, i8* %incdec.ptr.prol, align 1, !tbaa !12
  %incdec.ptr1.prol = getelementptr inbounds i8, i8* %to.addr.0.prol, i32 1
  store i8 %1, i8* %to.addr.0.prol, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !24

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %from.addr.0.unr = phi i8* [ %add.ptr, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %to.addr.0.unr = phi i8* [ %to, %entry ], [ %incdec.ptr1.prol, %do.body.prol ]
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %2 = icmp ult i32 %0, 3
  br i1 %2, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %from.addr.0 = phi i8* [ %incdec.ptr.3, %do.body ], [ %from.addr.0.unr, %do.body.prol.loopexit ]
  %to.addr.0 = phi i8* [ %incdec.ptr1.3, %do.body ], [ %to.addr.0.unr, %do.body.prol.loopexit ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %from.addr.0, i32 -1
  %3 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr1 = getelementptr inbounds i8, i8* %to.addr.0, i32 1
  store i8 %3, i8* %to.addr.0, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %from.addr.0, i32 -2
  %4 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr1.1 = getelementptr inbounds i8, i8* %to.addr.0, i32 2
  store i8 %4, i8* %incdec.ptr1, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %from.addr.0, i32 -3
  %5 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr1.2 = getelementptr inbounds i8, i8* %to.addr.0, i32 3
  store i8 %5, i8* %incdec.ptr1.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %from.addr.0, i32 -4
  %6 = load i8, i8* %incdec.ptr.3, align 1, !tbaa !12
  %incdec.ptr1.3 = getelementptr inbounds i8, i8* %to.addr.0, i32 4
  store i8 %6, i8* %incdec.ptr1.2, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  br i1 %tobool.not.3, label %do.end, label %do.body, !llvm.loop !25

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind
define hidden void @__leNtobe32(i8* nocapture readonly %from, i8* nocapture %to, i32 %length) local_unnamed_addr #1 {
entry:
  %add.ptr = getelementptr inbounds i8, i8* %to, i32 31
  %0 = add i32 %length, -1
  %xtraiter = and i32 %length, 3
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %from, %entry ]
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %add.ptr, %entry ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %from.addr.0.prol, i32 1
  %1 = load i8, i8* %from.addr.0.prol, align 1, !tbaa !12
  %incdec.ptr1.prol = getelementptr inbounds i8, i8* %to.addr.0.prol, i32 -1
  store i8 %1, i8* %to.addr.0.prol, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !26

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %from.addr.0.unr = phi i8* [ %from, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %to.addr.0.unr = phi i8* [ %add.ptr, %entry ], [ %incdec.ptr1.prol, %do.body.prol ]
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %2 = icmp ult i32 %0, 3
  br i1 %2, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %from.addr.0 = phi i8* [ %incdec.ptr.3, %do.body ], [ %from.addr.0.unr, %do.body.prol.loopexit ]
  %to.addr.0 = phi i8* [ %incdec.ptr1.3, %do.body ], [ %to.addr.0.unr, %do.body.prol.loopexit ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %from.addr.0, i32 1
  %3 = load i8, i8* %from.addr.0, align 1, !tbaa !12
  %incdec.ptr1 = getelementptr inbounds i8, i8* %to.addr.0, i32 -1
  store i8 %3, i8* %to.addr.0, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %from.addr.0, i32 2
  %4 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr1.1 = getelementptr inbounds i8, i8* %to.addr.0, i32 -2
  store i8 %4, i8* %incdec.ptr1, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %from.addr.0, i32 3
  %5 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr1.2 = getelementptr inbounds i8, i8* %to.addr.0, i32 -3
  store i8 %5, i8* %incdec.ptr1.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %from.addr.0, i32 4
  %6 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr1.3 = getelementptr inbounds i8, i8* %to.addr.0, i32 -4
  store i8 %6, i8* %incdec.ptr1.2, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  br i1 %tobool.not.3, label %do.end, label %do.body, !llvm.loop !27

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind
define hidden void @__leNtobeN(i8* nocapture readonly %from, i8* nocapture %to, i32 %length) local_unnamed_addr #1 {
entry:
  %add.ptr = getelementptr inbounds i8, i8* %to, i32 %length
  %0 = add i32 %length, -1
  %xtraiter = and i32 %length, 3
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol

do.body.prol:                                     ; preds = %entry, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %from, %entry ]
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %add.ptr, %entry ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %entry ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %entry ]
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %from.addr.0.prol, i32 1
  %1 = load i8, i8* %from.addr.0.prol, align 1, !tbaa !12
  %incdec.ptr1.prol = getelementptr inbounds i8, i8* %to.addr.0.prol, i32 -1
  store i8 %1, i8* %incdec.ptr1.prol, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !28

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %from.addr.0.unr = phi i8* [ %from, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %to.addr.0.unr = phi i8* [ %add.ptr, %entry ], [ %incdec.ptr1.prol, %do.body.prol ]
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %2 = icmp ult i32 %0, 3
  br i1 %2, label %do.end, label %do.body

do.body:                                          ; preds = %do.body.prol.loopexit, %do.body
  %from.addr.0 = phi i8* [ %incdec.ptr.3, %do.body ], [ %from.addr.0.unr, %do.body.prol.loopexit ]
  %to.addr.0 = phi i8* [ %incdec.ptr1.3, %do.body ], [ %to.addr.0.unr, %do.body.prol.loopexit ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %from.addr.0, i32 1
  %3 = load i8, i8* %from.addr.0, align 1, !tbaa !12
  %incdec.ptr1 = getelementptr inbounds i8, i8* %to.addr.0, i32 -1
  store i8 %3, i8* %incdec.ptr1, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %from.addr.0, i32 2
  %4 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr1.1 = getelementptr inbounds i8, i8* %to.addr.0, i32 -2
  store i8 %4, i8* %incdec.ptr1.1, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %from.addr.0, i32 3
  %5 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr1.2 = getelementptr inbounds i8, i8* %to.addr.0, i32 -3
  store i8 %5, i8* %incdec.ptr1.2, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %from.addr.0, i32 4
  %6 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr1.3 = getelementptr inbounds i8, i8* %to.addr.0, i32 -4
  store i8 %6, i8* %incdec.ptr1.3, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  br i1 %tobool.not.3, label %do.end, label %do.body, !llvm.loop !29

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nounwind
define hidden %struct.vector.0* @vector_new(i32 %members, i32 %size, i8* readonly %initial) local_unnamed_addr #3 {
entry:
  %mul = mul i32 %size, %members
  %add = add i32 %mul, 8
  %call = tail call i8* @__malloc(i32 %add) #17
  %len = bitcast i8* %call to i32*
  store i32 %members, i32* %len, align 4, !tbaa !30
  %size1 = getelementptr inbounds i8, i8* %call, i32 4
  %0 = bitcast i8* %size1 to i32*
  store i32 %members, i32* %0, align 4, !tbaa !30
  %data2 = getelementptr inbounds i8, i8* %call, i32 8
  %cmp.not = icmp eq i8* %initial, inttoptr (i32 -1 to i8*)
  %tobool6.not27 = icmp eq i32 %mul, 0
  br i1 %cmp.not, label %while.cond4.preheader, label %while.cond.preheader

while.cond.preheader:                             ; preds = %entry
  br i1 %tobool6.not27, label %if.end, label %while.body.preheader

while.body.preheader:                             ; preds = %while.cond.preheader
  %1 = add i32 %mul, -1
  %xtraiter = and i32 %mul, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol

while.body.prol:                                  ; preds = %while.body.preheader, %while.body.prol
  %data.026.prol = phi i8* [ %incdec.ptr3.prol, %while.body.prol ], [ %data2, %while.body.preheader ]
  %size_array.025.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %mul, %while.body.preheader ]
  %initial.addr.024.prol = phi i8* [ %incdec.ptr.prol, %while.body.prol ], [ %initial, %while.body.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.preheader ]
  %dec.prol = add i32 %size_array.025.prol, -1
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %initial.addr.024.prol, i32 1
  %2 = load i8, i8* %initial.addr.024.prol, align 1, !tbaa !12
  %incdec.ptr3.prol = getelementptr inbounds i8, i8* %data.026.prol, i32 1
  store i8 %2, i8* %data.026.prol, align 1, !tbaa !12
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %while.body.prol.loopexit, label %while.body.prol, !llvm.loop !32

while.body.prol.loopexit:                         ; preds = %while.body.prol, %while.body.preheader
  %data.026.unr = phi i8* [ %data2, %while.body.preheader ], [ %incdec.ptr3.prol, %while.body.prol ]
  %size_array.025.unr = phi i32 [ %mul, %while.body.preheader ], [ %dec.prol, %while.body.prol ]
  %initial.addr.024.unr = phi i8* [ %initial, %while.body.preheader ], [ %incdec.ptr.prol, %while.body.prol ]
  %3 = icmp ult i32 %1, 7
  br i1 %3, label %if.end, label %while.body

while.cond4.preheader:                            ; preds = %entry
  br i1 %tobool6.not27, label %if.end, label %while.body7.preheader

while.body7.preheader:                            ; preds = %while.cond4.preheader
  %4 = add i32 %mul, -1
  %xtraiter34 = and i32 %mul, 7
  %lcmp.mod35.not = icmp eq i32 %xtraiter34, 0
  br i1 %lcmp.mod35.not, label %while.body7.prol.loopexit, label %while.body7.prol

while.body7.prol:                                 ; preds = %while.body7.preheader, %while.body7.prol
  %data.129.prol = phi i8* [ %incdec.ptr8.prol, %while.body7.prol ], [ %data2, %while.body7.preheader ]
  %size_array.128.prol = phi i32 [ %dec5.prol, %while.body7.prol ], [ %mul, %while.body7.preheader ]
  %prol.iter36 = phi i32 [ %prol.iter36.sub, %while.body7.prol ], [ %xtraiter34, %while.body7.preheader ]
  %dec5.prol = add i32 %size_array.128.prol, -1
  %incdec.ptr8.prol = getelementptr inbounds i8, i8* %data.129.prol, i32 1
  store i8 0, i8* %data.129.prol, align 1, !tbaa !12
  %prol.iter36.sub = add i32 %prol.iter36, -1
  %prol.iter36.cmp.not = icmp eq i32 %prol.iter36.sub, 0
  br i1 %prol.iter36.cmp.not, label %while.body7.prol.loopexit, label %while.body7.prol, !llvm.loop !33

while.body7.prol.loopexit:                        ; preds = %while.body7.prol, %while.body7.preheader
  %data.129.unr = phi i8* [ %data2, %while.body7.preheader ], [ %incdec.ptr8.prol, %while.body7.prol ]
  %size_array.128.unr = phi i32 [ %mul, %while.body7.preheader ], [ %dec5.prol, %while.body7.prol ]
  %5 = icmp ult i32 %4, 7
  br i1 %5, label %if.end, label %while.body7

while.body:                                       ; preds = %while.body.prol.loopexit, %while.body
  %data.026 = phi i8* [ %incdec.ptr3.7, %while.body ], [ %data.026.unr, %while.body.prol.loopexit ]
  %size_array.025 = phi i32 [ %dec.7, %while.body ], [ %size_array.025.unr, %while.body.prol.loopexit ]
  %initial.addr.024 = phi i8* [ %incdec.ptr.7, %while.body ], [ %initial.addr.024.unr, %while.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %initial.addr.024, i32 1
  %6 = load i8, i8* %initial.addr.024, align 1, !tbaa !12
  %incdec.ptr3 = getelementptr inbounds i8, i8* %data.026, i32 1
  store i8 %6, i8* %data.026, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %initial.addr.024, i32 2
  %7 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr3.1 = getelementptr inbounds i8, i8* %data.026, i32 2
  store i8 %7, i8* %incdec.ptr3, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %initial.addr.024, i32 3
  %8 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr3.2 = getelementptr inbounds i8, i8* %data.026, i32 3
  store i8 %8, i8* %incdec.ptr3.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %initial.addr.024, i32 4
  %9 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr3.3 = getelementptr inbounds i8, i8* %data.026, i32 4
  store i8 %9, i8* %incdec.ptr3.2, align 1, !tbaa !12
  %incdec.ptr.4 = getelementptr inbounds i8, i8* %initial.addr.024, i32 5
  %10 = load i8, i8* %incdec.ptr.3, align 1, !tbaa !12
  %incdec.ptr3.4 = getelementptr inbounds i8, i8* %data.026, i32 5
  store i8 %10, i8* %incdec.ptr3.3, align 1, !tbaa !12
  %incdec.ptr.5 = getelementptr inbounds i8, i8* %initial.addr.024, i32 6
  %11 = load i8, i8* %incdec.ptr.4, align 1, !tbaa !12
  %incdec.ptr3.5 = getelementptr inbounds i8, i8* %data.026, i32 6
  store i8 %11, i8* %incdec.ptr3.4, align 1, !tbaa !12
  %incdec.ptr.6 = getelementptr inbounds i8, i8* %initial.addr.024, i32 7
  %12 = load i8, i8* %incdec.ptr.5, align 1, !tbaa !12
  %incdec.ptr3.6 = getelementptr inbounds i8, i8* %data.026, i32 7
  store i8 %12, i8* %incdec.ptr3.5, align 1, !tbaa !12
  %dec.7 = add i32 %size_array.025, -8
  %incdec.ptr.7 = getelementptr inbounds i8, i8* %initial.addr.024, i32 8
  %13 = load i8, i8* %incdec.ptr.6, align 1, !tbaa !12
  %incdec.ptr3.7 = getelementptr inbounds i8, i8* %data.026, i32 8
  store i8 %13, i8* %incdec.ptr3.6, align 1, !tbaa !12
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %if.end, label %while.body, !llvm.loop !34

while.body7:                                      ; preds = %while.body7.prol.loopexit, %while.body7
  %data.129 = phi i8* [ %incdec.ptr8.7, %while.body7 ], [ %data.129.unr, %while.body7.prol.loopexit ]
  %size_array.128 = phi i32 [ %dec5.7, %while.body7 ], [ %size_array.128.unr, %while.body7.prol.loopexit ]
  %incdec.ptr8 = getelementptr inbounds i8, i8* %data.129, i32 1
  store i8 0, i8* %data.129, align 1, !tbaa !12
  %incdec.ptr8.1 = getelementptr inbounds i8, i8* %data.129, i32 2
  store i8 0, i8* %incdec.ptr8, align 1, !tbaa !12
  %incdec.ptr8.2 = getelementptr inbounds i8, i8* %data.129, i32 3
  store i8 0, i8* %incdec.ptr8.1, align 1, !tbaa !12
  %incdec.ptr8.3 = getelementptr inbounds i8, i8* %data.129, i32 4
  store i8 0, i8* %incdec.ptr8.2, align 1, !tbaa !12
  %incdec.ptr8.4 = getelementptr inbounds i8, i8* %data.129, i32 5
  store i8 0, i8* %incdec.ptr8.3, align 1, !tbaa !12
  %incdec.ptr8.5 = getelementptr inbounds i8, i8* %data.129, i32 6
  store i8 0, i8* %incdec.ptr8.4, align 1, !tbaa !12
  %incdec.ptr8.6 = getelementptr inbounds i8, i8* %data.129, i32 7
  store i8 0, i8* %incdec.ptr8.5, align 1, !tbaa !12
  %dec5.7 = add i32 %size_array.128, -8
  %incdec.ptr8.7 = getelementptr inbounds i8, i8* %data.129, i32 8
  store i8 0, i8* %incdec.ptr8.6, align 1, !tbaa !12
  %tobool6.not.7 = icmp eq i32 %dec5.7, 0
  br i1 %tobool6.not.7, label %if.end, label %while.body7, !llvm.loop !35

if.end:                                           ; preds = %while.body.prol.loopexit, %while.body, %while.body7.prol.loopexit, %while.body7, %while.cond.preheader, %while.cond4.preheader
  %14 = bitcast i8* %call to %struct.vector.0*
  ret %struct.vector.0* %14
}

; Function Attrs: noinline nounwind
define hidden nonnull i8* @__malloc(i32 %size) local_unnamed_addr #4 {
entry:
  br label %land.rhs

land.rhs:                                         ; preds = %while.body, %entry
  %cur.012 = phi %struct.chunk.1* [ inttoptr (i32 65536 to %struct.chunk.1*), %entry ], [ %2, %while.body ]
  %allocated = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.012, i32 0, i32 3
  %0 = load i32, i32* %allocated, align 4, !tbaa !36
  %tobool1.not = icmp eq i32 %0, 0
  br i1 %tobool1.not, label %lor.rhs, label %while.body

lor.rhs:                                          ; preds = %land.rhs
  %length = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.012, i32 0, i32 2
  %1 = load i32, i32* %length, align 4, !tbaa !40
  %cmp = icmp ult i32 %1, %size
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %land.rhs, %lor.rhs
  %next = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.012, i32 0, i32 0
  %2 = load %struct.chunk.1*, %struct.chunk.1** %next, align 4, !tbaa !41
  %tobool.not = icmp eq %struct.chunk.1* %2, null
  br i1 %tobool.not, label %while.body.while.end_crit_edge, label %land.rhs

while.body.while.end_crit_edge:                   ; preds = %while.body
  %.pre = load i32, i32* inttoptr (i32 8 to i32*), align 8, !tbaa !40
  br label %while.end

while.end:                                        ; preds = %lor.rhs, %while.body.while.end_crit_edge
  %3 = phi i32 [ %.pre, %while.body.while.end_crit_edge ], [ %1, %lor.rhs ]
  %cur.0.lcssa = phi %struct.chunk.1* [ null, %while.body.while.end_crit_edge ], [ %cur.012, %lor.rhs ]
  %tobool.lcssa = phi i1 [ false, %while.body.while.end_crit_edge ], [ true, %lor.rhs ]
  tail call void @llvm.assume(i1 %tobool.lcssa)
  %add.i = add i32 %size, 7
  %and.i = and i32 %add.i, -8
  %length.i = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.0.lcssa, i32 0, i32 2
  %sub.i = sub i32 %3, %and.i
  %cmp.i = icmp ugt i32 %sub.i, 23
  br i1 %cmp.i, label %if.then.i, label %shrink_chunk.exit

if.then.i:                                        ; preds = %while.end
  %add.ptr.i = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.0.lcssa, i32 1
  %4 = bitcast %struct.chunk.1* %add.ptr.i to i8*
  %add.ptr1.i = getelementptr i8, i8* %4, i32 %and.i
  %next.i = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.0.lcssa, i32 0, i32 0
  %5 = load %struct.chunk.1*, %struct.chunk.1** %next.i, align 4, !tbaa !41
  %next2.i = bitcast i8* %add.ptr1.i to %struct.chunk.1**
  store %struct.chunk.1* %5, %struct.chunk.1** %next2.i, align 4, !tbaa !41
  %cmp3.not.i = icmp eq %struct.chunk.1* %5, null
  br i1 %cmp3.not.i, label %if.end.i, label %if.then4.i

if.then4.i:                                       ; preds = %if.then.i
  %prev.i = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %5, i32 0, i32 1
  %6 = bitcast %struct.chunk.1** %prev.i to i8**
  store i8* %add.ptr1.i, i8** %6, align 4, !tbaa !42
  br label %if.end.i

if.end.i:                                         ; preds = %if.then4.i, %if.then.i
  %7 = bitcast %struct.chunk.1* %cur.0.lcssa to i8**
  store i8* %add.ptr1.i, i8** %7, align 4, !tbaa !41
  %prev7.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 4
  %8 = bitcast i8* %prev7.i to %struct.chunk.1**
  store %struct.chunk.1* %cur.0.lcssa, %struct.chunk.1** %8, align 4, !tbaa !42
  %allocated.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 12
  %9 = bitcast i8* %allocated.i to i32*
  store i32 0, i32* %9, align 4, !tbaa !36
  %sub10.i = add i32 %sub.i, -16
  %length11.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 8
  %10 = bitcast i8* %length11.i to i32*
  store i32 %sub10.i, i32* %10, align 4, !tbaa !40
  store i32 %and.i, i32* %length.i, align 4, !tbaa !40
  br label %shrink_chunk.exit

shrink_chunk.exit:                                ; preds = %while.end, %if.end.i
  %allocated3 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.0.lcssa, i32 0, i32 3
  store i32 1, i32* %allocated3, align 4, !tbaa !36
  %incdec.ptr = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %cur.0.lcssa, i32 1
  %11 = bitcast %struct.chunk.1* %incdec.ptr to i8*
  ret i8* %11
}

; Function Attrs: inaccessiblememonly nofree nosync nounwind willreturn
declare void @llvm.assume(i1 noundef) #5

; Function Attrs: nofree norecurse nosync nounwind readonly
define hidden i64 @vector_hash(%struct.vector.0* nocapture readonly %v) local_unnamed_addr #2 {
entry:
  %len2 = getelementptr inbounds %struct.vector.0, %struct.vector.0* %v, i32 0, i32 0
  %0 = load i32, i32* %len2, align 4, !tbaa !30
  %tobool.not8 = icmp eq i32 %0, 0
  br i1 %tobool.not8, label %while.end, label %while.body.lr.ph

while.body.lr.ph:                                 ; preds = %entry
  %arraydecay = getelementptr inbounds %struct.vector.0, %struct.vector.0* %v, i32 0, i32 2, i32 0
  %1 = load i8, i8* %arraydecay, align 1, !tbaa !12
  %conv = zext i8 %1 to i64
  %2 = add i32 %0, -1
  %3 = zext i32 %2 to i64
  %4 = add nuw nsw i64 %3, 1
  %5 = mul nuw nsw i64 %4, %conv
  br label %while.end

while.end:                                        ; preds = %while.body.lr.ph, %entry
  %hash.0.lcssa = phi i64 [ 0, %entry ], [ %5, %while.body.lr.ph ]
  ret i64 %hash.0.lcssa
}

; Function Attrs: nofree norecurse nosync nounwind readonly
define hidden zeroext i1 @__memcmp(i8* nocapture readonly %left, i32 %left_len, i8* nocapture readonly %right, i32 %right_len) local_unnamed_addr #2 {
entry:
  %cmp.not = icmp eq i32 %left_len, %right_len
  br i1 %cmp.not, label %while.cond, label %return

while.cond:                                       ; preds = %entry, %while.body
  %left.addr.0 = phi i8* [ %incdec.ptr, %while.body ], [ %left, %entry ]
  %left_len.addr.0 = phi i32 [ %dec, %while.body ], [ %left_len, %entry ]
  %right.addr.0 = phi i8* [ %incdec.ptr1, %while.body ], [ %right, %entry ]
  %tobool.not = icmp eq i32 %left_len.addr.0, 0
  br i1 %tobool.not, label %return, label %while.body

while.body:                                       ; preds = %while.cond
  %dec = add i32 %left_len.addr.0, -1
  %incdec.ptr = getelementptr inbounds i8, i8* %left.addr.0, i32 1
  %0 = load i8, i8* %left.addr.0, align 1, !tbaa !12
  %incdec.ptr1 = getelementptr inbounds i8, i8* %right.addr.0, i32 1
  %1 = load i8, i8* %right.addr.0, align 1, !tbaa !12
  %cmp3.not = icmp eq i8 %0, %1
  br i1 %cmp3.not, label %while.cond, label %return, !llvm.loop !43

return:                                           ; preds = %while.cond, %while.body, %entry
  %retval.0 = phi i1 [ false, %entry ], [ %tobool.not, %while.body ], [ %tobool.not, %while.cond ]
  ret i1 %retval.0
}

; Function Attrs: nounwind
define hidden %struct.vector.0* @concat(i8* nocapture readonly %left, i32 %left_len, i8* nocapture readonly %right, i32 %right_len) local_unnamed_addr #3 {
entry:
  %add = add i32 %right_len, %left_len
  %add1 = add i32 %add, 8
  %call = tail call i8* @__malloc(i32 %add1) #17
  %len = bitcast i8* %call to i32*
  store i32 %add, i32* %len, align 4, !tbaa !30
  %size = getelementptr inbounds i8, i8* %call, i32 4
  %0 = bitcast i8* %size to i32*
  store i32 %add, i32* %0, align 4, !tbaa !30
  %data2 = getelementptr inbounds i8, i8* %call, i32 8
  %tobool.not22 = icmp eq i32 %left_len, 0
  br i1 %tobool.not22, label %while.cond4.preheader, label %while.body.preheader

while.body.preheader:                             ; preds = %entry
  %1 = add i32 %left_len, -1
  %xtraiter = and i32 %left_len, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol

while.body.prol:                                  ; preds = %while.body.preheader, %while.body.prol
  %data.025.prol = phi i8* [ %incdec.ptr3.prol, %while.body.prol ], [ %data2, %while.body.preheader ]
  %left.addr.024.prol = phi i8* [ %incdec.ptr.prol, %while.body.prol ], [ %left, %while.body.preheader ]
  %left_len.addr.023.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %left_len, %while.body.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.preheader ]
  %dec.prol = add i32 %left_len.addr.023.prol, -1
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %left.addr.024.prol, i32 1
  %2 = load i8, i8* %left.addr.024.prol, align 1, !tbaa !12
  %incdec.ptr3.prol = getelementptr inbounds i8, i8* %data.025.prol, i32 1
  store i8 %2, i8* %data.025.prol, align 1, !tbaa !12
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %while.body.prol.loopexit, label %while.body.prol, !llvm.loop !44

while.body.prol.loopexit:                         ; preds = %while.body.prol, %while.body.preheader
  %incdec.ptr3.lcssa.unr = phi i8* [ undef, %while.body.preheader ], [ %incdec.ptr3.prol, %while.body.prol ]
  %data.025.unr = phi i8* [ %data2, %while.body.preheader ], [ %incdec.ptr3.prol, %while.body.prol ]
  %left.addr.024.unr = phi i8* [ %left, %while.body.preheader ], [ %incdec.ptr.prol, %while.body.prol ]
  %left_len.addr.023.unr = phi i32 [ %left_len, %while.body.preheader ], [ %dec.prol, %while.body.prol ]
  %3 = icmp ult i32 %1, 7
  br i1 %3, label %while.cond4.preheader, label %while.body

while.cond4.preheader:                            ; preds = %while.body.prol.loopexit, %while.body, %entry
  %data.0.lcssa = phi i8* [ %data2, %entry ], [ %incdec.ptr3.lcssa.unr, %while.body.prol.loopexit ], [ %incdec.ptr3.7, %while.body ]
  %tobool6.not26 = icmp eq i32 %right_len, 0
  br i1 %tobool6.not26, label %while.end10, label %while.body7.preheader

while.body7.preheader:                            ; preds = %while.cond4.preheader
  %4 = add i32 %right_len, -1
  %xtraiter30 = and i32 %right_len, 7
  %lcmp.mod31.not = icmp eq i32 %xtraiter30, 0
  br i1 %lcmp.mod31.not, label %while.body7.prol.loopexit, label %while.body7.prol

while.body7.prol:                                 ; preds = %while.body7.preheader, %while.body7.prol
  %data.129.prol = phi i8* [ %incdec.ptr9.prol, %while.body7.prol ], [ %data.0.lcssa, %while.body7.preheader ]
  %right_len.addr.028.prol = phi i32 [ %dec5.prol, %while.body7.prol ], [ %right_len, %while.body7.preheader ]
  %right.addr.027.prol = phi i8* [ %incdec.ptr8.prol, %while.body7.prol ], [ %right, %while.body7.preheader ]
  %prol.iter32 = phi i32 [ %prol.iter32.sub, %while.body7.prol ], [ %xtraiter30, %while.body7.preheader ]
  %dec5.prol = add i32 %right_len.addr.028.prol, -1
  %incdec.ptr8.prol = getelementptr inbounds i8, i8* %right.addr.027.prol, i32 1
  %5 = load i8, i8* %right.addr.027.prol, align 1, !tbaa !12
  %incdec.ptr9.prol = getelementptr inbounds i8, i8* %data.129.prol, i32 1
  store i8 %5, i8* %data.129.prol, align 1, !tbaa !12
  %prol.iter32.sub = add i32 %prol.iter32, -1
  %prol.iter32.cmp.not = icmp eq i32 %prol.iter32.sub, 0
  br i1 %prol.iter32.cmp.not, label %while.body7.prol.loopexit, label %while.body7.prol, !llvm.loop !45

while.body7.prol.loopexit:                        ; preds = %while.body7.prol, %while.body7.preheader
  %data.129.unr = phi i8* [ %data.0.lcssa, %while.body7.preheader ], [ %incdec.ptr9.prol, %while.body7.prol ]
  %right_len.addr.028.unr = phi i32 [ %right_len, %while.body7.preheader ], [ %dec5.prol, %while.body7.prol ]
  %right.addr.027.unr = phi i8* [ %right, %while.body7.preheader ], [ %incdec.ptr8.prol, %while.body7.prol ]
  %6 = icmp ult i32 %4, 7
  br i1 %6, label %while.end10, label %while.body7

while.body:                                       ; preds = %while.body.prol.loopexit, %while.body
  %data.025 = phi i8* [ %incdec.ptr3.7, %while.body ], [ %data.025.unr, %while.body.prol.loopexit ]
  %left.addr.024 = phi i8* [ %incdec.ptr.7, %while.body ], [ %left.addr.024.unr, %while.body.prol.loopexit ]
  %left_len.addr.023 = phi i32 [ %dec.7, %while.body ], [ %left_len.addr.023.unr, %while.body.prol.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %left.addr.024, i32 1
  %7 = load i8, i8* %left.addr.024, align 1, !tbaa !12
  %incdec.ptr3 = getelementptr inbounds i8, i8* %data.025, i32 1
  store i8 %7, i8* %data.025, align 1, !tbaa !12
  %incdec.ptr.1 = getelementptr inbounds i8, i8* %left.addr.024, i32 2
  %8 = load i8, i8* %incdec.ptr, align 1, !tbaa !12
  %incdec.ptr3.1 = getelementptr inbounds i8, i8* %data.025, i32 2
  store i8 %8, i8* %incdec.ptr3, align 1, !tbaa !12
  %incdec.ptr.2 = getelementptr inbounds i8, i8* %left.addr.024, i32 3
  %9 = load i8, i8* %incdec.ptr.1, align 1, !tbaa !12
  %incdec.ptr3.2 = getelementptr inbounds i8, i8* %data.025, i32 3
  store i8 %9, i8* %incdec.ptr3.1, align 1, !tbaa !12
  %incdec.ptr.3 = getelementptr inbounds i8, i8* %left.addr.024, i32 4
  %10 = load i8, i8* %incdec.ptr.2, align 1, !tbaa !12
  %incdec.ptr3.3 = getelementptr inbounds i8, i8* %data.025, i32 4
  store i8 %10, i8* %incdec.ptr3.2, align 1, !tbaa !12
  %incdec.ptr.4 = getelementptr inbounds i8, i8* %left.addr.024, i32 5
  %11 = load i8, i8* %incdec.ptr.3, align 1, !tbaa !12
  %incdec.ptr3.4 = getelementptr inbounds i8, i8* %data.025, i32 5
  store i8 %11, i8* %incdec.ptr3.3, align 1, !tbaa !12
  %incdec.ptr.5 = getelementptr inbounds i8, i8* %left.addr.024, i32 6
  %12 = load i8, i8* %incdec.ptr.4, align 1, !tbaa !12
  %incdec.ptr3.5 = getelementptr inbounds i8, i8* %data.025, i32 6
  store i8 %12, i8* %incdec.ptr3.4, align 1, !tbaa !12
  %incdec.ptr.6 = getelementptr inbounds i8, i8* %left.addr.024, i32 7
  %13 = load i8, i8* %incdec.ptr.5, align 1, !tbaa !12
  %incdec.ptr3.6 = getelementptr inbounds i8, i8* %data.025, i32 7
  store i8 %13, i8* %incdec.ptr3.5, align 1, !tbaa !12
  %dec.7 = add i32 %left_len.addr.023, -8
  %incdec.ptr.7 = getelementptr inbounds i8, i8* %left.addr.024, i32 8
  %14 = load i8, i8* %incdec.ptr.6, align 1, !tbaa !12
  %incdec.ptr3.7 = getelementptr inbounds i8, i8* %data.025, i32 8
  store i8 %14, i8* %incdec.ptr3.6, align 1, !tbaa !12
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  br i1 %tobool.not.7, label %while.cond4.preheader, label %while.body, !llvm.loop !46

while.body7:                                      ; preds = %while.body7.prol.loopexit, %while.body7
  %data.129 = phi i8* [ %incdec.ptr9.7, %while.body7 ], [ %data.129.unr, %while.body7.prol.loopexit ]
  %right_len.addr.028 = phi i32 [ %dec5.7, %while.body7 ], [ %right_len.addr.028.unr, %while.body7.prol.loopexit ]
  %right.addr.027 = phi i8* [ %incdec.ptr8.7, %while.body7 ], [ %right.addr.027.unr, %while.body7.prol.loopexit ]
  %incdec.ptr8 = getelementptr inbounds i8, i8* %right.addr.027, i32 1
  %15 = load i8, i8* %right.addr.027, align 1, !tbaa !12
  %incdec.ptr9 = getelementptr inbounds i8, i8* %data.129, i32 1
  store i8 %15, i8* %data.129, align 1, !tbaa !12
  %incdec.ptr8.1 = getelementptr inbounds i8, i8* %right.addr.027, i32 2
  %16 = load i8, i8* %incdec.ptr8, align 1, !tbaa !12
  %incdec.ptr9.1 = getelementptr inbounds i8, i8* %data.129, i32 2
  store i8 %16, i8* %incdec.ptr9, align 1, !tbaa !12
  %incdec.ptr8.2 = getelementptr inbounds i8, i8* %right.addr.027, i32 3
  %17 = load i8, i8* %incdec.ptr8.1, align 1, !tbaa !12
  %incdec.ptr9.2 = getelementptr inbounds i8, i8* %data.129, i32 3
  store i8 %17, i8* %incdec.ptr9.1, align 1, !tbaa !12
  %incdec.ptr8.3 = getelementptr inbounds i8, i8* %right.addr.027, i32 4
  %18 = load i8, i8* %incdec.ptr8.2, align 1, !tbaa !12
  %incdec.ptr9.3 = getelementptr inbounds i8, i8* %data.129, i32 4
  store i8 %18, i8* %incdec.ptr9.2, align 1, !tbaa !12
  %incdec.ptr8.4 = getelementptr inbounds i8, i8* %right.addr.027, i32 5
  %19 = load i8, i8* %incdec.ptr8.3, align 1, !tbaa !12
  %incdec.ptr9.4 = getelementptr inbounds i8, i8* %data.129, i32 5
  store i8 %19, i8* %incdec.ptr9.3, align 1, !tbaa !12
  %incdec.ptr8.5 = getelementptr inbounds i8, i8* %right.addr.027, i32 6
  %20 = load i8, i8* %incdec.ptr8.4, align 1, !tbaa !12
  %incdec.ptr9.5 = getelementptr inbounds i8, i8* %data.129, i32 6
  store i8 %20, i8* %incdec.ptr9.4, align 1, !tbaa !12
  %incdec.ptr8.6 = getelementptr inbounds i8, i8* %right.addr.027, i32 7
  %21 = load i8, i8* %incdec.ptr8.5, align 1, !tbaa !12
  %incdec.ptr9.6 = getelementptr inbounds i8, i8* %data.129, i32 7
  store i8 %21, i8* %incdec.ptr9.5, align 1, !tbaa !12
  %dec5.7 = add i32 %right_len.addr.028, -8
  %incdec.ptr8.7 = getelementptr inbounds i8, i8* %right.addr.027, i32 8
  %22 = load i8, i8* %incdec.ptr8.6, align 1, !tbaa !12
  %incdec.ptr9.7 = getelementptr inbounds i8, i8* %data.129, i32 8
  store i8 %22, i8* %incdec.ptr9.6, align 1, !tbaa !12
  %tobool6.not.7 = icmp eq i32 %dec5.7, 0
  br i1 %tobool6.not.7, label %while.end10, label %while.body7, !llvm.loop !47

while.end10:                                      ; preds = %while.body7.prol.loopexit, %while.body7, %while.cond4.preheader
  %23 = bitcast i8* %call to %struct.vector.0*
  ret %struct.vector.0* %23
}

; Function Attrs: nofree nounwind
define hidden void @__init_heap() local_unnamed_addr #6 {
entry:
  store %struct.chunk.1* null, %struct.chunk.1** inttoptr (i32 65540 to %struct.chunk.1**), align 4, !tbaa !42
  store %struct.chunk.1* null, %struct.chunk.1** inttoptr (i32 65536 to %struct.chunk.1**), align 65536, !tbaa !41
  store i32 0, i32* inttoptr (i32 65548 to i32*), align 4, !tbaa !36
  %0 = tail call i32 @llvm.wasm.memory.size.i32(i32 0)
  %mul = shl i32 %0, 16
  %sub1 = add i32 %mul, -65552
  store i32 %sub1, i32* inttoptr (i32 65544 to i32*), align 8, !tbaa !40
  ret void
}

; Function Attrs: nounwind readonly
declare i32 @llvm.wasm.memory.size.i32(i32) #7

; Function Attrs: nofree noinline norecurse nounwind
define hidden void @__free(i8* %m) local_unnamed_addr #8 {
entry:
  %incdec.ptr = getelementptr inbounds i8, i8* %m, i32 -16
  %tobool.not = icmp eq i8* %m, null
  br i1 %tobool.not, label %if.end28, label %if.then

if.then:                                          ; preds = %entry
  %allocated = getelementptr inbounds i8, i8* %m, i32 -4
  %0 = bitcast i8* %allocated to i32*
  store i32 0, i32* %0, align 4, !tbaa !36
  %next1 = bitcast i8* %incdec.ptr to %struct.chunk.1**
  %1 = load %struct.chunk.1*, %struct.chunk.1** %next1, align 4, !tbaa !41
  %tobool2.not = icmp eq %struct.chunk.1* %1, null
  br i1 %tobool2.not, label %if.end13, label %land.lhs.true

land.lhs.true:                                    ; preds = %if.then
  %allocated3 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %1, i32 0, i32 3
  %2 = load i32, i32* %allocated3, align 4, !tbaa !36
  %tobool4.not = icmp eq i32 %2, 0
  br i1 %tobool4.not, label %if.then5, label %if.end13

if.then5:                                         ; preds = %land.lhs.true
  %next6 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %1, i32 0, i32 0
  %3 = load %struct.chunk.1*, %struct.chunk.1** %next6, align 4, !tbaa !41
  store %struct.chunk.1* %3, %struct.chunk.1** %next1, align 4, !tbaa !41
  %cmp.not = icmp eq %struct.chunk.1* %3, null
  br i1 %cmp.not, label %if.end, label %if.then8

if.then8:                                         ; preds = %if.then5
  %prev = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %3, i32 0, i32 1
  %4 = bitcast %struct.chunk.1** %prev to i8**
  store i8* %incdec.ptr, i8** %4, align 4, !tbaa !42
  br label %if.end

if.end:                                           ; preds = %if.then5, %if.then8
  %length = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %1, i32 0, i32 2
  %5 = load i32, i32* %length, align 4, !tbaa !40
  %add = add i32 %5, 16
  %length10 = getelementptr inbounds i8, i8* %m, i32 -8
  %6 = bitcast i8* %length10 to i32*
  %7 = load i32, i32* %6, align 4, !tbaa !40
  %add11 = add i32 %add, %7
  store i32 %add11, i32* %6, align 4, !tbaa !40
  br label %if.end13

if.end13:                                         ; preds = %land.lhs.true, %if.then, %if.end
  %next.0 = phi %struct.chunk.1* [ %1, %land.lhs.true ], [ %3, %if.end ], [ null, %if.then ]
  %prev15 = getelementptr inbounds i8, i8* %m, i32 -12
  %8 = bitcast i8* %prev15 to %struct.chunk.1**
  %9 = load %struct.chunk.1*, %struct.chunk.1** %8, align 4, !tbaa !42
  %tobool16.not = icmp eq %struct.chunk.1* %9, null
  br i1 %tobool16.not, label %if.end28, label %land.lhs.true17

land.lhs.true17:                                  ; preds = %if.end13
  %allocated18 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %9, i32 0, i32 3
  %10 = load i32, i32* %allocated18, align 4, !tbaa !36
  %tobool19.not = icmp eq i32 %10, 0
  br i1 %tobool19.not, label %if.then20, label %if.end28

if.then20:                                        ; preds = %land.lhs.true17
  %next21 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %9, i32 0, i32 0
  store %struct.chunk.1* %next.0, %struct.chunk.1** %next21, align 4, !tbaa !41
  %prev22 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %next.0, i32 0, i32 1
  store %struct.chunk.1* %9, %struct.chunk.1** %prev22, align 4, !tbaa !42
  %length23 = getelementptr inbounds i8, i8* %m, i32 -8
  %11 = bitcast i8* %length23 to i32*
  %12 = load i32, i32* %11, align 4, !tbaa !40
  %add24 = add i32 %12, 16
  %length25 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %9, i32 0, i32 2
  %13 = load i32, i32* %length25, align 4, !tbaa !40
  %add26 = add i32 %add24, %13
  store i32 %add26, i32* %length25, align 4, !tbaa !40
  br label %if.end28

if.end28:                                         ; preds = %if.then20, %if.end13, %land.lhs.true17, %entry
  ret void
}

; Function Attrs: nounwind
define hidden i8* @__realloc(i8* %m, i32 %size) local_unnamed_addr #9 {
entry:
  %incdec.ptr = getelementptr inbounds i8, i8* %m, i32 -16
  %next1 = bitcast i8* %incdec.ptr to %struct.chunk.1**
  %0 = load %struct.chunk.1*, %struct.chunk.1** %next1, align 4, !tbaa !41
  %tobool.not = icmp eq %struct.chunk.1* %0, null
  br i1 %tobool.not, label %if.else, label %land.lhs.true

land.lhs.true:                                    ; preds = %entry
  %allocated = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %0, i32 0, i32 3
  %1 = load i32, i32* %allocated, align 4, !tbaa !36
  %tobool2.not = icmp eq i32 %1, 0
  br i1 %tobool2.not, label %land.lhs.true3, label %if.else

land.lhs.true3:                                   ; preds = %land.lhs.true
  %length = getelementptr inbounds i8, i8* %m, i32 -8
  %2 = bitcast i8* %length to i32*
  %3 = load i32, i32* %2, align 4, !tbaa !40
  %length4 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %0, i32 0, i32 2
  %4 = load i32, i32* %length4, align 4, !tbaa !40
  %add = add i32 %3, 16
  %add5 = add i32 %add, %4
  %cmp.not = icmp ult i32 %add5, %size
  br i1 %cmp.not, label %if.else, label %if.then

if.then:                                          ; preds = %land.lhs.true3
  %next6 = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %0, i32 0, i32 0
  %5 = load %struct.chunk.1*, %struct.chunk.1** %next6, align 4, !tbaa !41
  store %struct.chunk.1* %5, %struct.chunk.1** %next1, align 4, !tbaa !41
  %prev = getelementptr inbounds %struct.chunk.1, %struct.chunk.1* %5, i32 0, i32 1
  %6 = bitcast %struct.chunk.1** %prev to i8**
  store i8* %incdec.ptr, i8** %6, align 4, !tbaa !42
  store i32 %add5, i32* %2, align 4, !tbaa !40
  %add.i = add i32 %size, 7
  %and.i = and i32 %add.i, -8
  %sub.i = sub i32 %add5, %and.i
  %cmp.i = icmp ugt i32 %sub.i, 23
  br i1 %cmp.i, label %if.then.i, label %cleanup

if.then.i:                                        ; preds = %if.then
  %add.ptr1.i = getelementptr i8, i8* %m, i32 %and.i
  %next2.i = bitcast i8* %add.ptr1.i to %struct.chunk.1**
  store %struct.chunk.1* %5, %struct.chunk.1** %next2.i, align 4, !tbaa !41
  %cmp3.not.i = icmp eq %struct.chunk.1* %5, null
  br i1 %cmp3.not.i, label %if.end.i, label %if.then4.i

if.then4.i:                                       ; preds = %if.then.i
  store i8* %add.ptr1.i, i8** %6, align 4, !tbaa !42
  br label %if.end.i

if.end.i:                                         ; preds = %if.then4.i, %if.then.i
  %7 = bitcast i8* %incdec.ptr to i8**
  store i8* %add.ptr1.i, i8** %7, align 4, !tbaa !41
  %prev7.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 4
  %8 = bitcast i8* %prev7.i to i8**
  store i8* %incdec.ptr, i8** %8, align 4, !tbaa !42
  %allocated.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 12
  %9 = bitcast i8* %allocated.i to i32*
  store i32 0, i32* %9, align 4, !tbaa !36
  %sub10.i = add i32 %sub.i, -16
  %length11.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 8
  %10 = bitcast i8* %length11.i to i32*
  store i32 %sub10.i, i32* %10, align 4, !tbaa !40
  store i32 %and.i, i32* %2, align 4, !tbaa !40
  br label %cleanup

if.else:                                          ; preds = %land.lhs.true3, %land.lhs.true, %entry
  %call = tail call i8* @__malloc(i32 %size) #18
  %div = lshr i32 %size, 3
  tail call void @__memcpy8(i8* nonnull %call, i8* nonnull %m, i32 %div) #17
  tail call void @__free(i8* nonnull %m) #18
  br label %cleanup

cleanup:                                          ; preds = %if.end.i, %if.then, %if.else
  %retval.0 = phi i8* [ %call, %if.else ], [ %m, %if.then ], [ %m, %if.end.i ]
  ret i8* %retval.0
}

; Function Attrs: nofree nounwind
define hidden void @__mul32(i32* nocapture readonly %left, i32* nocapture readonly %right, i32* nocapture %out, i32 %len) local_unnamed_addr #6 {
entry:
  %0 = icmp slt i32 %len, 0
  %smin91 = select i1 %0, i32 %len, i32 0
  br label %while.cond

while.cond:                                       ; preds = %land.rhs, %entry
  %left_len.0 = phi i32 [ %len, %entry ], [ %sub, %land.rhs ]
  %cmp = icmp sgt i32 %left_len.0, 0
  br i1 %cmp, label %land.rhs, label %while.end

land.rhs:                                         ; preds = %while.cond
  %sub = add nsw i32 %left_len.0, -1
  %arrayidx = getelementptr inbounds i32, i32* %left, i32 %sub
  %1 = load i32, i32* %arrayidx, align 4, !tbaa !30
  %tobool.not = icmp eq i32 %1, 0
  br i1 %tobool.not, label %while.cond, label %while.end

while.end:                                        ; preds = %while.cond, %land.rhs
  %left_len.0.lcssa = phi i32 [ %smin91, %while.cond ], [ %left_len.0, %land.rhs ]
  br label %while.cond1

while.cond1:                                      ; preds = %land.rhs3, %while.end
  %right_len.0 = phi i32 [ %len, %while.end ], [ %sub4, %land.rhs3 ]
  %cmp2 = icmp sgt i32 %right_len.0, 0
  br i1 %cmp2, label %land.rhs3, label %while.end11

land.rhs3:                                        ; preds = %while.cond1
  %sub4 = add nsw i32 %right_len.0, -1
  %arrayidx5 = getelementptr inbounds i32, i32* %right, i32 %sub4
  %2 = load i32, i32* %arrayidx5, align 4, !tbaa !30
  %tobool6.not = icmp eq i32 %2, 0
  br i1 %tobool6.not, label %while.cond1, label %while.end11

while.end11:                                      ; preds = %while.cond1, %land.rhs3
  %right_len.0.lcssa = phi i32 [ %smin91, %while.cond1 ], [ %right_len.0, %land.rhs3 ]
  %cmp1285 = icmp sgt i32 %len, 0
  br i1 %cmp1285, label %for.body, label %for.cond.cleanup

for.cond.cleanup:                                 ; preds = %for.cond.cleanup25, %while.end11
  ret void

for.body:                                         ; preds = %while.end11, %for.cond.cleanup25
  %val1.090 = phi i64 [ %or, %for.cond.cleanup25 ], [ 0, %while.end11 ]
  %l.089 = phi i32 [ %inc38, %for.cond.cleanup25 ], [ 0, %while.end11 ]
  %left_start.088 = phi i32 [ %left_start.1, %for.cond.cleanup25 ], [ 0, %while.end11 ]
  %right_end.087 = phi i32 [ %spec.select76, %for.cond.cleanup25 ], [ 0, %while.end11 ]
  %right_start.086 = phi i32 [ %spec.select, %for.cond.cleanup25 ], [ 0, %while.end11 ]
  %cmp13.not = icmp sge i32 %l.089, %left_len.0.lcssa
  %inc = zext i1 %cmp13.not to i32
  %spec.select = add nuw nsw i32 %right_start.086, %inc
  %cmp14.not = icmp sge i32 %l.089, %right_len.0.lcssa
  %inc16 = zext i1 %cmp14.not to i32
  %left_start.1 = add nuw nsw i32 %left_start.088, %inc16
  %cmp18 = icmp slt i32 %right_end.087, %right_len.0.lcssa
  %inc20 = zext i1 %cmp18 to i32
  %spec.select76 = add nuw nsw i32 %right_end.087, %inc20
  %cmp24.not.not79 = icmp ugt i32 %spec.select76, %spec.select
  br i1 %cmp24.not.not79, label %for.body26, label %for.cond.cleanup25

for.cond.cleanup25.loopexit:                      ; preds = %for.body26
  %3 = extractvalue { i64, i1 } %6, 0
  br label %for.cond.cleanup25

for.cond.cleanup25:                               ; preds = %for.cond.cleanup25.loopexit, %for.body
  %carry.1.lcssa = phi i64 [ 0, %for.body ], [ %spec.select77, %for.cond.cleanup25.loopexit ]
  %val1.1.lcssa = phi i64 [ %val1.090, %for.body ], [ %3, %for.cond.cleanup25.loopexit ]
  %conv35 = trunc i64 %val1.1.lcssa to i32
  %arrayidx36 = getelementptr inbounds i32, i32* %out, i32 %l.089
  store i32 %conv35, i32* %arrayidx36, align 4, !tbaa !30
  %shr = lshr i64 %val1.1.lcssa, 32
  %or = or i64 %shr, %carry.1.lcssa
  %inc38 = add nuw nsw i32 %l.089, 1
  %exitcond.not = icmp eq i32 %inc38, %len
  br i1 %exitcond.not, label %for.cond.cleanup, label %for.body

for.body26:                                       ; preds = %for.body, %for.body26
  %r.083.in = phi i32 [ %r.083, %for.body26 ], [ %spec.select76, %for.body ]
  %val1.182 = phi i64 [ %8, %for.body26 ], [ %val1.090, %for.body ]
  %i.081 = phi i32 [ %inc30, %for.body26 ], [ 0, %for.body ]
  %carry.180 = phi i64 [ %spec.select77, %for.body26 ], [ 0, %for.body ]
  %r.083 = add nsw i32 %r.083.in, -1
  %add = add nuw nsw i32 %i.081, %left_start.1
  %arrayidx27 = getelementptr inbounds i32, i32* %left, i32 %add
  %4 = load i32, i32* %arrayidx27, align 4, !tbaa !30
  %conv = zext i32 %4 to i64
  %arrayidx28 = getelementptr inbounds i32, i32* %right, i32 %r.083
  %5 = load i32, i32* %arrayidx28, align 4, !tbaa !30
  %conv29 = zext i32 %5 to i64
  %mul = mul nuw i64 %conv29, %conv
  %inc30 = add nuw nsw i32 %i.081, 1
  %6 = tail call { i64, i1 } @llvm.uadd.with.overflow.i64(i64 %val1.182, i64 %mul)
  %7 = extractvalue { i64, i1 } %6, 1
  %8 = extractvalue { i64, i1 } %6, 0
  %add32 = add i64 %carry.180, 4294967296
  %spec.select77 = select i1 %7, i64 %add32, i64 %carry.180
  %cmp24.not.not = icmp sgt i32 %r.083, %spec.select
  br i1 %cmp24.not.not, label %for.body26, label %for.cond.cleanup25.loopexit
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare { i64, i1 } @llvm.uadd.with.overflow.i64(i64, i64) #10

; Function Attrs: norecurse nounwind readnone
define hidden i128 @__ashlti3(i128 %val, i32 %r) local_unnamed_addr #11 {
entry:
  %in.sroa.0.0.extract.trunc = trunc i128 %val to i64
  %in.sroa.7.0.extract.shift = lshr i128 %val, 64
  %in.sroa.7.0.extract.trunc = trunc i128 %in.sroa.7.0.extract.shift to i64
  %cmp = icmp eq i32 %r, 0
  br i1 %cmp, label %if.end17, label %if.else

if.else:                                          ; preds = %entry
  %and = and i32 %r, 64
  %tobool.not = icmp eq i32 %and, 0
  br i1 %tobool.not, label %if.else6, label %if.then3

if.then3:                                         ; preds = %if.else
  %and5 = and i32 %r, 63
  %sh_prom = zext i32 %and5 to i64
  %shl = shl i64 %in.sroa.0.0.extract.trunc, %sh_prom
  br label %if.end17

if.else6:                                         ; preds = %if.else
  %sh_prom8 = zext i32 %r to i64
  %shl9 = shl i64 %in.sroa.0.0.extract.trunc, %sh_prom8
  %shl13 = shl i64 %in.sroa.7.0.extract.trunc, %sh_prom8
  %sub = sub nsw i32 64, %r
  %sh_prom15 = zext i32 %sub to i64
  %shr = lshr i64 %in.sroa.0.0.extract.trunc, %sh_prom15
  %or = or i64 %shr, %shl13
  br label %if.end17

if.end17:                                         ; preds = %entry, %if.then3, %if.else6
  %result.sroa.6.0 = phi i64 [ %shl, %if.then3 ], [ %or, %if.else6 ], [ %in.sroa.7.0.extract.trunc, %entry ]
  %result.sroa.0.0 = phi i64 [ 0, %if.then3 ], [ %shl9, %if.else6 ], [ %in.sroa.0.0.extract.trunc, %entry ]
  %result.sroa.6.0.insert.ext = zext i64 %result.sroa.6.0 to i128
  %result.sroa.6.0.insert.shift = shl nuw i128 %result.sroa.6.0.insert.ext, 64
  %result.sroa.0.0.insert.ext = zext i64 %result.sroa.0.0 to i128
  %result.sroa.0.0.insert.insert = or i128 %result.sroa.6.0.insert.shift, %result.sroa.0.0.insert.ext
  ret i128 %result.sroa.0.0.insert.insert
}

; Function Attrs: norecurse nounwind readnone
define hidden i128 @__lshrti3(i128 %val, i32 %r) local_unnamed_addr #11 {
entry:
  %in.sroa.0.0.extract.trunc = trunc i128 %val to i64
  %in.sroa.5.0.extract.shift = lshr i128 %val, 64
  %in.sroa.5.0.extract.trunc = trunc i128 %in.sroa.5.0.extract.shift to i64
  %cmp = icmp eq i32 %r, 0
  br i1 %cmp, label %if.end17, label %if.else

if.else:                                          ; preds = %entry
  %and = and i32 %r, 64
  %tobool.not = icmp eq i32 %and, 0
  br i1 %tobool.not, label %if.else6, label %if.then3

if.then3:                                         ; preds = %if.else
  %and4 = and i32 %r, 63
  %sh_prom = zext i32 %and4 to i64
  %shr = lshr i64 %in.sroa.5.0.extract.trunc, %sh_prom
  br label %if.end17

if.else6:                                         ; preds = %if.else
  %sh_prom8 = zext i32 %r to i64
  %shr9 = lshr i64 %in.sroa.0.0.extract.trunc, %sh_prom8
  %sub = sub nsw i32 64, %r
  %sh_prom11 = zext i32 %sub to i64
  %shl = shl i64 %in.sroa.5.0.extract.trunc, %sh_prom11
  %or = or i64 %shl, %shr9
  %shr15 = lshr i64 %in.sroa.5.0.extract.trunc, %sh_prom8
  br label %if.end17

if.end17:                                         ; preds = %entry, %if.then3, %if.else6
  %result.sroa.6.0 = phi i64 [ 0, %if.then3 ], [ %shr15, %if.else6 ], [ %in.sroa.5.0.extract.trunc, %entry ]
  %result.sroa.0.0 = phi i64 [ %shr, %if.then3 ], [ %or, %if.else6 ], [ %in.sroa.0.0.extract.trunc, %entry ]
  %result.sroa.6.0.insert.ext = zext i64 %result.sroa.6.0 to i128
  %result.sroa.6.0.insert.shift = shl nuw i128 %result.sroa.6.0.insert.ext, 64
  %result.sroa.0.0.insert.ext = zext i64 %result.sroa.0.0 to i128
  %result.sroa.0.0.insert.insert = or i128 %result.sroa.6.0.insert.shift, %result.sroa.0.0.insert.ext
  ret i128 %result.sroa.0.0.insert.insert
}

; Function Attrs: norecurse nounwind readnone
define hidden i128 @__ashrti3(i128 %val, i32 %r) local_unnamed_addr #11 {
entry:
  %in.sroa.0.0.extract.trunc = trunc i128 %val to i64
  %in.sroa.5.0.extract.shift = lshr i128 %val, 64
  %in.sroa.5.0.extract.trunc = trunc i128 %in.sroa.5.0.extract.shift to i64
  %cmp = icmp eq i32 %r, 0
  br i1 %cmp, label %if.end19, label %if.else

if.else:                                          ; preds = %entry
  %and = and i32 %r, 64
  %tobool.not = icmp eq i32 %and, 0
  br i1 %tobool.not, label %if.else8, label %if.then3

if.then3:                                         ; preds = %if.else
  %shr = ashr i64 %in.sroa.5.0.extract.trunc, 63
  %and6 = and i32 %r, 63
  %sh_prom = zext i32 %and6 to i64
  %shr7 = ashr i64 %in.sroa.5.0.extract.trunc, %sh_prom
  br label %if.end19

if.else8:                                         ; preds = %if.else
  %sh_prom10 = zext i32 %r to i64
  %shr11 = lshr i64 %in.sroa.0.0.extract.trunc, %sh_prom10
  %sub = sub nsw i32 64, %r
  %sh_prom13 = zext i32 %sub to i64
  %shl = shl i64 %in.sroa.5.0.extract.trunc, %sh_prom13
  %or = or i64 %shl, %shr11
  %shr17 = ashr i64 %in.sroa.5.0.extract.trunc, %sh_prom10
  br label %if.end19

if.end19:                                         ; preds = %entry, %if.then3, %if.else8
  %result.sroa.6.0 = phi i64 [ %shr, %if.then3 ], [ %shr17, %if.else8 ], [ %in.sroa.5.0.extract.trunc, %entry ]
  %result.sroa.0.0 = phi i64 [ %shr7, %if.then3 ], [ %or, %if.else8 ], [ %in.sroa.0.0.extract.trunc, %entry ]
  %result.sroa.6.0.insert.ext = zext i64 %result.sroa.6.0 to i128
  %result.sroa.6.0.insert.shift = shl nuw i128 %result.sroa.6.0.insert.ext, 64
  %result.sroa.0.0.insert.ext = zext i64 %result.sroa.0.0 to i128
  %result.sroa.0.0.insert.insert = or i128 %result.sroa.6.0.insert.shift, %result.sroa.0.0.insert.ext
  ret i128 %result.sroa.0.0.insert.insert
}

; Function Attrs: norecurse nounwind readnone
define hidden i32 @bits(i64 %v) local_unnamed_addr #11 {
entry:
  %tobool.not = icmp ult i64 %v, 4294967296
  %shl = shl i64 %v, 32
  %spec.select = select i1 %tobool.not, i64 %shl, i64 %v
  %spec.select47 = select i1 %tobool.not, i32 31, i32 63
  %tobool2.not = icmp ult i64 %spec.select, 281474976710656
  %sub4 = add nsw i32 %spec.select47, -16
  %shl5 = shl i64 %spec.select, 16
  %v.addr.1 = select i1 %tobool2.not, i64 %shl5, i64 %spec.select
  %h.1 = select i1 %tobool2.not, i32 %sub4, i32 %spec.select47
  %tobool8.not = icmp ult i64 %v.addr.1, 72057594037927936
  %sub10 = add nsw i32 %h.1, -8
  %shl11 = shl i64 %v.addr.1, 8
  %v.addr.2 = select i1 %tobool8.not, i64 %shl11, i64 %v.addr.1
  %h.2 = select i1 %tobool8.not, i32 %sub10, i32 %h.1
  %tobool14.not = icmp ult i64 %v.addr.2, 1152921504606846976
  %sub16 = add nsw i32 %h.2, -4
  %shl17 = shl i64 %v.addr.2, 4
  %v.addr.3 = select i1 %tobool14.not, i64 %shl17, i64 %v.addr.2
  %h.3 = select i1 %tobool14.not, i32 %sub16, i32 %h.2
  %tobool20.not = icmp ult i64 %v.addr.3, 4611686018427387904
  %sub22 = add nsw i32 %h.3, -2
  %shl23 = shl i64 %v.addr.3, 2
  %v.addr.4 = select i1 %tobool20.not, i64 %shl23, i64 %v.addr.3
  %h.4 = select i1 %tobool20.not, i32 %sub22, i32 %h.3
  %v.addr.4.lobit = ashr i64 %v.addr.4, 63
  %0 = trunc i64 %v.addr.4.lobit to i32
  %.not = xor i32 %0, -1
  %spec.select48 = add nsw i32 %h.4, %.not
  ret i32 %spec.select48
}

; Function Attrs: norecurse nounwind readnone
define hidden i32 @bits128(i128 %v) local_unnamed_addr #11 {
entry:
  %shr = lshr i128 %v, 64
  %conv = trunc i128 %shr to i64
  %tobool.not = icmp eq i64 %conv, 0
  br i1 %tobool.not, label %if.else, label %if.then

if.then:                                          ; preds = %entry
  %tobool.not.i = icmp ult i64 %conv, 4294967296
  %shl.i33 = shl nuw nsw i128 %shr, 32
  %shl.i = trunc i128 %shl.i33 to i64
  %spec.select.i = select i1 %tobool.not.i, i64 %shl.i, i64 %conv
  %spec.select47.i = select i1 %tobool.not.i, i32 31, i32 63
  %tobool2.not.i = icmp ult i64 %spec.select.i, 281474976710656
  %sub4.i = add nsw i32 %spec.select47.i, -16
  %shl5.i = shl i64 %spec.select.i, 16
  %v.addr.1.i = select i1 %tobool2.not.i, i64 %shl5.i, i64 %spec.select.i
  %h.1.i = select i1 %tobool2.not.i, i32 %sub4.i, i32 %spec.select47.i
  %tobool8.not.i = icmp ult i64 %v.addr.1.i, 72057594037927936
  %sub10.i = add nsw i32 %h.1.i, -8
  %shl11.i = shl i64 %v.addr.1.i, 8
  %v.addr.2.i = select i1 %tobool8.not.i, i64 %shl11.i, i64 %v.addr.1.i
  %h.2.i = select i1 %tobool8.not.i, i32 %sub10.i, i32 %h.1.i
  %tobool14.not.i = icmp ult i64 %v.addr.2.i, 1152921504606846976
  %sub16.i = add nsw i32 %h.2.i, -4
  %shl17.i = shl i64 %v.addr.2.i, 4
  %v.addr.3.i = select i1 %tobool14.not.i, i64 %shl17.i, i64 %v.addr.2.i
  %h.3.i = select i1 %tobool14.not.i, i32 %sub16.i, i32 %h.2.i
  %tobool20.not.i = icmp ult i64 %v.addr.3.i, 4611686018427387904
  %sub22.i = add nsw i32 %h.3.i, -2
  %shl23.i = shl i64 %v.addr.3.i, 2
  %v.addr.4.i = select i1 %tobool20.not.i, i64 %shl23.i, i64 %v.addr.3.i
  %h.4.i = select i1 %tobool20.not.i, i32 %sub22.i, i32 %h.3.i
  %v.addr.4.lobit.i = ashr i64 %v.addr.4.i, 63
  %0 = trunc i64 %v.addr.4.lobit.i to i32
  %.not.i = xor i32 %0, -1
  %spec.select48.i = add nuw nsw i32 %h.4.i, 64
  %add = add i32 %spec.select48.i, %.not.i
  br label %cleanup

if.else:                                          ; preds = %entry
  %conv1 = trunc i128 %v to i64
  %tobool.not.i6 = icmp ult i64 %conv1, 4294967296
  %shl.i7 = shl i64 %conv1, 32
  %spec.select.i8 = select i1 %tobool.not.i6, i64 %shl.i7, i64 %conv1
  %spec.select47.i9 = select i1 %tobool.not.i6, i32 31, i32 63
  %tobool2.not.i10 = icmp ult i64 %spec.select.i8, 281474976710656
  %sub4.i11 = add nsw i32 %spec.select47.i9, -16
  %shl5.i12 = shl i64 %spec.select.i8, 16
  %v.addr.1.i13 = select i1 %tobool2.not.i10, i64 %shl5.i12, i64 %spec.select.i8
  %h.1.i14 = select i1 %tobool2.not.i10, i32 %sub4.i11, i32 %spec.select47.i9
  %tobool8.not.i15 = icmp ult i64 %v.addr.1.i13, 72057594037927936
  %sub10.i16 = add nsw i32 %h.1.i14, -8
  %shl11.i17 = shl i64 %v.addr.1.i13, 8
  %v.addr.2.i18 = select i1 %tobool8.not.i15, i64 %shl11.i17, i64 %v.addr.1.i13
  %h.2.i19 = select i1 %tobool8.not.i15, i32 %sub10.i16, i32 %h.1.i14
  %tobool14.not.i20 = icmp ult i64 %v.addr.2.i18, 1152921504606846976
  %sub16.i21 = add nsw i32 %h.2.i19, -4
  %shl17.i22 = shl i64 %v.addr.2.i18, 4
  %v.addr.3.i23 = select i1 %tobool14.not.i20, i64 %shl17.i22, i64 %v.addr.2.i18
  %h.3.i24 = select i1 %tobool14.not.i20, i32 %sub16.i21, i32 %h.2.i19
  %tobool20.not.i25 = icmp ult i64 %v.addr.3.i23, 4611686018427387904
  %sub22.i26 = add nsw i32 %h.3.i24, -2
  %shl23.i27 = shl i64 %v.addr.3.i23, 2
  %v.addr.4.i28 = select i1 %tobool20.not.i25, i64 %shl23.i27, i64 %v.addr.3.i23
  %h.4.i29 = select i1 %tobool20.not.i25, i32 %sub22.i26, i32 %h.3.i24
  %v.addr.4.lobit.i30 = ashr i64 %v.addr.4.i28, 63
  %1 = trunc i64 %v.addr.4.lobit.i30 to i32
  %.not.i31 = xor i32 %1, -1
  %spec.select48.i32 = add nsw i32 %h.4.i29, %.not.i31
  br label %cleanup

cleanup:                                          ; preds = %if.else, %if.then
  %retval.0 = phi i32 [ %add, %if.then ], [ %spec.select48.i32, %if.else ]
  ret i32 %retval.0
}

; Function Attrs: norecurse nounwind readnone
define hidden i128 @shl128(i128 %val, i32 %r) local_unnamed_addr #11 {
entry:
  %cmp = icmp eq i32 %r, 0
  br i1 %cmp, label %return, label %if.else

if.else:                                          ; preds = %entry
  %and = and i32 %r, 64
  %tobool.not = icmp eq i32 %and, 0
  %conv7 = trunc i128 %val to i64
  br i1 %tobool.not, label %if.else5, label %if.then1

if.then1:                                         ; preds = %if.else
  %and2 = and i32 %r, 63
  %sh_prom = zext i32 %and2 to i64
  %shl = shl i64 %conv7, %sh_prom
  %conv3 = zext i64 %shl to i128
  %shl4 = shl nuw i128 %conv3, 64
  br label %return

if.else5:                                         ; preds = %if.else
  %shr = lshr i128 %val, 64
  %conv8 = trunc i128 %shr to i64
  %sh_prom10 = zext i32 %r to i64
  %shl11 = shl i64 %conv8, %sh_prom10
  %sub = sub nsw i32 64, %r
  %sh_prom12 = zext i32 %sub to i64
  %shr13 = lshr i64 %conv7, %sh_prom12
  %or = or i64 %shr13, %shl11
  %conv14 = zext i64 %or to i128
  %shl16 = shl i64 %conv7, %sh_prom10
  %conv17 = zext i64 %shl16 to i128
  %shl18 = shl nuw i128 %conv14, 64
  %or19 = or i128 %shl18, %conv17
  br label %return

return:                                           ; preds = %entry, %if.else5, %if.then1
  %retval.0 = phi i128 [ %shl4, %if.then1 ], [ %or19, %if.else5 ], [ %val, %entry ]
  ret i128 %retval.0
}

; Function Attrs: norecurse nounwind readnone
define hidden i128 @shr128(i128 %val, i32 %r) local_unnamed_addr #11 {
entry:
  %cmp = icmp eq i32 %r, 0
  br i1 %cmp, label %return, label %if.else

if.else:                                          ; preds = %entry
  %and = and i32 %r, 64
  %tobool.not = icmp eq i32 %and, 0
  br i1 %tobool.not, label %if.else5, label %if.then1

if.then1:                                         ; preds = %if.else
  %shr = lshr i128 %val, 64
  %conv = trunc i128 %shr to i64
  %and2 = and i32 %r, 63
  %sh_prom = zext i32 %and2 to i64
  %shr3 = lshr i64 %conv, %sh_prom
  %conv4 = zext i64 %shr3 to i128
  br label %return

if.else5:                                         ; preds = %if.else
  %conv6 = trunc i128 %val to i64
  %shr8 = lshr i128 %val, 64
  %conv9 = trunc i128 %shr8 to i64
  %sh_prom10 = zext i32 %r to i64
  %shr11 = lshr i64 %conv6, %sh_prom10
  %sub = sub nsw i32 64, %r
  %sh_prom12 = zext i32 %sub to i64
  %shl = shl i64 %conv9, %sh_prom12
  %conv13 = zext i64 %shl to i128
  %conv14 = zext i64 %shr11 to i128
  %shl15 = shl nuw i128 %conv13, 64
  %or = or i128 %shl15, %conv14
  br label %return

return:                                           ; preds = %entry, %if.else5, %if.then1
  %retval.0 = phi i128 [ %conv4, %if.then1 ], [ %or, %if.else5 ], [ %val, %entry ]
  ret i128 %retval.0
}

; Function Attrs: nofree norecurse nounwind
define hidden i32 @udivmod128(i128* nocapture readonly %pdividend, i128* nocapture readonly %pdivisor, i128* nocapture %remainder, i128* nocapture %quotient) local_unnamed_addr #12 {
entry:
  %0 = load i128, i128* %pdividend, align 16, !tbaa !48
  %1 = load i128, i128* %pdivisor, align 16, !tbaa !48
  switch i128 %1, label %if.end3 [
    i128 0, label %cleanup
    i128 1, label %if.then2
  ]

if.then2:                                         ; preds = %entry
  store i128 0, i128* %remainder, align 16, !tbaa !48
  store i128 %0, i128* %quotient, align 16, !tbaa !48
  br label %cleanup

if.end3:                                          ; preds = %entry
  %cmp4 = icmp eq i128 %1, %0
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %if.end3
  store i128 0, i128* %remainder, align 16, !tbaa !48
  store i128 1, i128* %quotient, align 16, !tbaa !48
  br label %cleanup

if.end6:                                          ; preds = %if.end3
  %cmp7 = icmp eq i128 %0, 0
  %cmp8 = icmp ult i128 %0, %1
  %or.cond = or i1 %cmp7, %cmp8
  br i1 %or.cond, label %if.then9, label %if.end10

if.then9:                                         ; preds = %if.end6
  store i128 %0, i128* %remainder, align 16, !tbaa !48
  store i128 0, i128* %quotient, align 16, !tbaa !48
  br label %cleanup

if.end10:                                         ; preds = %if.end6
  %call = tail call i32 @bits128(i128 %0) #18
  %cmp1152 = icmp sgt i32 %call, -1
  br i1 %cmp1152, label %for.body.preheader, label %for.cond.cleanup

for.body.preheader:                               ; preds = %if.end10
  %add = add nuw nsw i32 %call, 1
  br label %for.body

for.cond.cleanup:                                 ; preds = %for.body, %if.end10
  %q.0.lcssa = phi i128 [ 0, %if.end10 ], [ %q.1, %for.body ]
  %r.0.lcssa = phi i128 [ 0, %if.end10 ], [ %r.2, %for.body ]
  store i128 %q.0.lcssa, i128* %quotient, align 16, !tbaa !48
  store i128 %r.0.lcssa, i128* %remainder, align 16, !tbaa !48
  br label %cleanup

for.body:                                         ; preds = %for.body.preheader, %for.body
  %x.055 = phi i32 [ %sub, %for.body ], [ %add, %for.body.preheader ]
  %r.054 = phi i128 [ %r.2, %for.body ], [ 0, %for.body.preheader ]
  %q.053 = phi i128 [ %q.1, %for.body ], [ 0, %for.body.preheader ]
  %shl = shl i128 %q.053, 1
  %shl12 = shl i128 %r.054, 1
  %sub = add nsw i32 %x.055, -1
  %sh_prom = zext i32 %sub to i128
  %2 = shl nuw i128 1, %sh_prom
  %3 = and i128 %2, %0
  %tobool.not = icmp ne i128 %3, 0
  %inc = zext i1 %tobool.not to i128
  %spec.select = or i128 %shl12, %inc
  %cmp15.not = icmp ult i128 %spec.select, %1
  %not.cmp15.not = xor i1 %cmp15.not, true
  %inc18 = zext i1 %not.cmp15.not to i128
  %q.1 = or i128 %shl, %inc18
  %sub17 = select i1 %cmp15.not, i128 0, i128 %1
  %r.2 = sub i128 %spec.select, %sub17
  %cmp11 = icmp sgt i32 %x.055, 1
  br i1 %cmp11, label %for.body, label %for.cond.cleanup

cleanup:                                          ; preds = %entry, %for.cond.cleanup, %if.then9, %if.then5, %if.then2
  %retval.0 = phi i32 [ 0, %if.then2 ], [ 0, %if.then5 ], [ 0, %if.then9 ], [ 0, %for.cond.cleanup ], [ 1, %entry ]
  ret i32 %retval.0
}

; Function Attrs: nofree norecurse nounwind
define hidden i32 @sdivmod128(i128* nocapture %pdividend, i128* nocapture %pdivisor, i128* nocapture %remainder, i128* nocapture %quotient) local_unnamed_addr #12 {
entry:
  %0 = bitcast i128* %pdividend to i8*
  %arrayidx = getelementptr inbounds i8, i8* %0, i32 15
  %1 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %cmp = icmp slt i8 %1, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %2 = load i128, i128* %pdividend, align 16, !tbaa !48
  %sub = sub i128 0, %2
  store i128 %sub, i128* %pdividend, align 16, !tbaa !48
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %3 = bitcast i128* %pdivisor to i8*
  %arrayidx2 = getelementptr inbounds i8, i8* %3, i32 15
  %4 = load i8, i8* %arrayidx2, align 1, !tbaa !12
  %cmp4 = icmp slt i8 %4, 0
  %5 = load i128, i128* %pdivisor, align 16, !tbaa !48
  br i1 %cmp4, label %if.then8, label %if.end10

if.then8:                                         ; preds = %if.end
  %sub9 = sub i128 0, %5
  store i128 %sub9, i128* %pdivisor, align 16, !tbaa !48
  br label %if.end10

if.end10:                                         ; preds = %if.end, %if.then8
  %6 = phi i128 [ %sub9, %if.then8 ], [ %5, %if.end ]
  %7 = load i128, i128* %pdividend, align 16, !tbaa !48
  switch i128 %6, label %if.end3.i [
    i128 0, label %cleanup
    i128 1, label %if.then2.i
  ]

if.then2.i:                                       ; preds = %if.end10
  store i128 0, i128* %remainder, align 16, !tbaa !48
  store i128 %7, i128* %quotient, align 16, !tbaa !48
  br label %if.end13

if.end3.i:                                        ; preds = %if.end10
  %cmp4.i = icmp eq i128 %6, %7
  br i1 %cmp4.i, label %if.then5.i, label %if.end6.i

if.then5.i:                                       ; preds = %if.end3.i
  store i128 0, i128* %remainder, align 16, !tbaa !48
  store i128 1, i128* %quotient, align 16, !tbaa !48
  br label %if.end13

if.end6.i:                                        ; preds = %if.end3.i
  %cmp7.i = icmp eq i128 %7, 0
  %cmp8.i = icmp ult i128 %7, %6
  %or.cond.i = or i1 %cmp7.i, %cmp8.i
  br i1 %or.cond.i, label %if.then9.i, label %if.end10.i

if.then9.i:                                       ; preds = %if.end6.i
  store i128 %7, i128* %remainder, align 16, !tbaa !48
  store i128 0, i128* %quotient, align 16, !tbaa !48
  br label %if.end13

if.end10.i:                                       ; preds = %if.end6.i
  %call.i = tail call i32 @bits128(i128 %7) #17
  %cmp1152.i = icmp sgt i32 %call.i, -1
  br i1 %cmp1152.i, label %for.body.preheader.i, label %for.cond.cleanup.i

for.body.preheader.i:                             ; preds = %if.end10.i
  %add.i = add nuw nsw i32 %call.i, 1
  br label %for.body.i

for.cond.cleanup.i:                               ; preds = %for.body.i, %if.end10.i
  %q.0.lcssa.i = phi i128 [ 0, %if.end10.i ], [ %q.1.i, %for.body.i ]
  %r.0.lcssa.i = phi i128 [ 0, %if.end10.i ], [ %r.2.i, %for.body.i ]
  store i128 %q.0.lcssa.i, i128* %quotient, align 16, !tbaa !48
  store i128 %r.0.lcssa.i, i128* %remainder, align 16, !tbaa !48
  br label %if.end13

for.body.i:                                       ; preds = %for.body.i, %for.body.preheader.i
  %x.055.i = phi i32 [ %sub.i, %for.body.i ], [ %add.i, %for.body.preheader.i ]
  %r.054.i = phi i128 [ %r.2.i, %for.body.i ], [ 0, %for.body.preheader.i ]
  %q.053.i = phi i128 [ %q.1.i, %for.body.i ], [ 0, %for.body.preheader.i ]
  %shl.i = shl i128 %q.053.i, 1
  %shl12.i = shl i128 %r.054.i, 1
  %sub.i = add nsw i32 %x.055.i, -1
  %sh_prom.i = zext i32 %sub.i to i128
  %8 = shl nuw i128 1, %sh_prom.i
  %9 = and i128 %8, %7
  %tobool.not.i = icmp ne i128 %9, 0
  %inc.i = zext i1 %tobool.not.i to i128
  %spec.select.i = or i128 %shl12.i, %inc.i
  %cmp15.not.i = icmp ult i128 %spec.select.i, %6
  %not.cmp15.not.i = xor i1 %cmp15.not.i, true
  %inc18.i = zext i1 %not.cmp15.not.i to i128
  %q.1.i = or i128 %shl.i, %inc18.i
  %sub17.i = select i1 %cmp15.not.i, i128 0, i128 %6
  %r.2.i = sub i128 %spec.select.i, %sub17.i
  %cmp11.i = icmp sgt i32 %x.055.i, 1
  br i1 %cmp11.i, label %for.body.i, label %for.cond.cleanup.i

if.end13:                                         ; preds = %if.then2.i, %if.then5.i, %if.then9.i, %for.cond.cleanup.i
  %cmp18.not.unshifted = xor i8 %4, %1
  %cmp18.not = icmp sgt i8 %cmp18.not.unshifted, -1
  br i1 %cmp18.not, label %if.end22, label %if.then20

if.then20:                                        ; preds = %if.end13
  %10 = load i128, i128* %quotient, align 16, !tbaa !48
  %sub21 = sub i128 0, %10
  store i128 %sub21, i128* %quotient, align 16, !tbaa !48
  br label %if.end22

if.end22:                                         ; preds = %if.end13, %if.then20
  br i1 %cmp, label %if.then24, label %cleanup

if.then24:                                        ; preds = %if.end22
  %11 = load i128, i128* %remainder, align 16, !tbaa !48
  %sub25 = sub i128 0, %11
  store i128 %sub25, i128* %remainder, align 16, !tbaa !48
  br label %cleanup

cleanup:                                          ; preds = %if.end10, %if.end22, %if.then24
  %retval.0 = phi i32 [ 0, %if.then24 ], [ 0, %if.end22 ], [ 1, %if.end10 ]
  ret i32 %retval.0
}

; Function Attrs: norecurse nounwind readonly
define hidden i32 @bits256(i256* nocapture readonly %value) local_unnamed_addr #13 {
entry:
  %0 = bitcast i256* %value to i64*
  %arrayidx = getelementptr inbounds i64, i64* %0, i32 3
  %1 = load i64, i64* %arrayidx, align 8, !tbaa !4
  %tobool.not = icmp eq i64 %1, 0
  br i1 %tobool.not, label %for.inc, label %cleanup

for.inc:                                          ; preds = %entry
  %arrayidx.1 = getelementptr inbounds i64, i64* %0, i32 2
  %2 = load i64, i64* %arrayidx.1, align 8, !tbaa !4
  %tobool.not.1 = icmp eq i64 %2, 0
  br i1 %tobool.not.1, label %for.inc.1, label %cleanup

cleanup:                                          ; preds = %for.inc.2, %for.inc.1, %for.inc, %entry
  %i.013.lcssa = phi i32 [ 192, %entry ], [ 128, %for.inc ], [ 64, %for.inc.1 ], [ 0, %for.inc.2 ]
  %.lcssa = phi i64 [ %1, %entry ], [ %2, %for.inc ], [ %5, %for.inc.1 ], [ %6, %for.inc.2 ]
  %tobool.not.i = icmp ult i64 %.lcssa, 4294967296
  %shl.i = shl i64 %.lcssa, 32
  %spec.select.i = select i1 %tobool.not.i, i64 %shl.i, i64 %.lcssa
  %spec.select47.i = select i1 %tobool.not.i, i32 31, i32 63
  %tobool2.not.i = icmp ult i64 %spec.select.i, 281474976710656
  %sub4.i = add nsw i32 %spec.select47.i, -16
  %shl5.i = shl i64 %spec.select.i, 16
  %v.addr.1.i = select i1 %tobool2.not.i, i64 %shl5.i, i64 %spec.select.i
  %h.1.i = select i1 %tobool2.not.i, i32 %sub4.i, i32 %spec.select47.i
  %tobool8.not.i = icmp ult i64 %v.addr.1.i, 72057594037927936
  %sub10.i = add nsw i32 %h.1.i, -8
  %shl11.i = shl i64 %v.addr.1.i, 8
  %v.addr.2.i = select i1 %tobool8.not.i, i64 %shl11.i, i64 %v.addr.1.i
  %h.2.i = select i1 %tobool8.not.i, i32 %sub10.i, i32 %h.1.i
  %tobool14.not.i = icmp ult i64 %v.addr.2.i, 1152921504606846976
  %sub16.i = add nsw i32 %h.2.i, -4
  %shl17.i = shl i64 %v.addr.2.i, 4
  %v.addr.3.i = select i1 %tobool14.not.i, i64 %shl17.i, i64 %v.addr.2.i
  %h.3.i = select i1 %tobool14.not.i, i32 %sub16.i, i32 %h.2.i
  %tobool20.not.i = icmp ult i64 %v.addr.3.i, 4611686018427387904
  %sub22.i = add nsw i32 %h.3.i, -2
  %shl23.i = shl i64 %v.addr.3.i, 2
  %v.addr.4.i = select i1 %tobool20.not.i, i64 %shl23.i, i64 %v.addr.3.i
  %h.4.i = select i1 %tobool20.not.i, i32 %sub22.i, i32 %h.3.i
  %v.addr.4.lobit.i = ashr i64 %v.addr.4.i, 63
  %3 = trunc i64 %v.addr.4.lobit.i to i32
  %.not.i = xor i32 %3, -1
  %spec.select48.i = add nuw nsw i32 %h.4.i, %i.013.lcssa
  %add = add i32 %spec.select48.i, %.not.i
  br label %.loopexit

.loopexit:                                        ; preds = %for.inc.2, %cleanup
  %4 = phi i32 [ %add, %cleanup ], [ 0, %for.inc.2 ]
  ret i32 %4

for.inc.1:                                        ; preds = %for.inc
  %arrayidx.2 = getelementptr inbounds i64, i64* %0, i32 1
  %5 = load i64, i64* %arrayidx.2, align 8, !tbaa !4
  %tobool.not.2 = icmp eq i64 %5, 0
  br i1 %tobool.not.2, label %for.inc.2, label %cleanup

for.inc.2:                                        ; preds = %for.inc.1
  %6 = load i64, i64* %0, align 8, !tbaa !4
  %tobool.not.3 = icmp eq i64 %6, 0
  br i1 %tobool.not.3, label %.loopexit, label %cleanup
}

; Function Attrs: nounwind
define hidden i32 @udivmod256(i256* nocapture readonly %pdividend, i256* nocapture readonly %pdivisor, i256* nocapture %remainder, i256* nocapture %quotient) local_unnamed_addr #9 {
entry:
  %0 = load i256, i256* %pdividend, align 8, !tbaa !50
  %dividend.sroa.0.0.extract.trunc = trunc i256 %0 to i64
  %dividend.sroa.9.0.extract.shift = lshr i256 %0, 64
  %dividend.sroa.9.0.extract.trunc = trunc i256 %dividend.sroa.9.0.extract.shift to i64
  %dividend.sroa.11.0.extract.shift = lshr i256 %0, 128
  %dividend.sroa.11.0.extract.trunc = trunc i256 %dividend.sroa.11.0.extract.shift to i64
  %dividend.sroa.13.0.extract.shift = lshr i256 %0, 192
  %dividend.sroa.13.0.extract.trunc = trunc i256 %dividend.sroa.13.0.extract.shift to i64
  %1 = load i256, i256* %pdivisor, align 8, !tbaa !50
  %divisor.sroa.0.0.extract.trunc = trunc i256 %1 to i64
  %divisor.sroa.6.0.extract.shift = lshr i256 %1, 64
  %divisor.sroa.6.0.extract.trunc = trunc i256 %divisor.sroa.6.0.extract.shift to i64
  %divisor.sroa.8.0.extract.shift = lshr i256 %1, 128
  %divisor.sroa.8.0.extract.trunc = trunc i256 %divisor.sroa.8.0.extract.shift to i64
  %divisor.sroa.10.0.extract.shift = lshr i256 %1, 192
  %divisor.sroa.10.0.extract.trunc = trunc i256 %divisor.sroa.10.0.extract.shift to i64
  switch i256 %1, label %if.end3 [
    i256 0, label %cleanup
    i256 1, label %if.then2
  ]

if.then2:                                         ; preds = %entry
  store i256 0, i256* %remainder, align 8, !tbaa !50
  store i256 %0, i256* %quotient, align 8, !tbaa !50
  br label %cleanup

if.end3:                                          ; preds = %entry
  %cmp4 = icmp eq i256 %1, %0
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %if.end3
  store i256 0, i256* %remainder, align 8, !tbaa !50
  store i256 1, i256* %quotient, align 8, !tbaa !50
  br label %cleanup

if.end6:                                          ; preds = %if.end3
  %cmp7 = icmp eq i256 %0, 0
  %cmp8 = icmp ult i256 %0, %1
  %or.cond = or i1 %cmp7, %cmp8
  br i1 %or.cond, label %if.then9, label %if.end10

if.then9:                                         ; preds = %if.end6
  store i256 %0, i256* %remainder, align 8, !tbaa !50
  store i256 0, i256* %quotient, align 8, !tbaa !50
  br label %cleanup

if.end10:                                         ; preds = %if.end6
  %tobool.not.i = icmp eq i64 %dividend.sroa.13.0.extract.trunc, 0
  br i1 %tobool.not.i, label %for.inc.i, label %cleanup.i

for.inc.i:                                        ; preds = %if.end10
  %tobool.not.1.i = icmp eq i64 %dividend.sroa.11.0.extract.trunc, 0
  br i1 %tobool.not.1.i, label %for.inc.1.i, label %cleanup.i

cleanup.i:                                        ; preds = %for.inc.2.i, %for.inc.1.i, %for.inc.i, %if.end10
  %i.013.lcssa.i = phi i32 [ 192, %if.end10 ], [ 128, %for.inc.i ], [ 64, %for.inc.1.i ], [ 0, %for.inc.2.i ]
  %.lcssa.i = phi i64 [ %dividend.sroa.13.0.extract.trunc, %if.end10 ], [ %dividend.sroa.11.0.extract.trunc, %for.inc.i ], [ %dividend.sroa.9.0.extract.trunc, %for.inc.1.i ], [ %dividend.sroa.0.0.extract.trunc, %for.inc.2.i ]
  %tobool.not.i.i = icmp ult i64 %.lcssa.i, 4294967296
  %shl.i.i = shl i64 %.lcssa.i, 32
  %spec.select.i.i = select i1 %tobool.not.i.i, i64 %shl.i.i, i64 %.lcssa.i
  %spec.select47.i.i = select i1 %tobool.not.i.i, i32 31, i32 63
  %tobool2.not.i.i = icmp ult i64 %spec.select.i.i, 281474976710656
  %sub4.i.i = add nsw i32 %spec.select47.i.i, -16
  %shl5.i.i = shl i64 %spec.select.i.i, 16
  %v.addr.1.i.i = select i1 %tobool2.not.i.i, i64 %shl5.i.i, i64 %spec.select.i.i
  %h.1.i.i = select i1 %tobool2.not.i.i, i32 %sub4.i.i, i32 %spec.select47.i.i
  %tobool8.not.i.i = icmp ult i64 %v.addr.1.i.i, 72057594037927936
  %sub10.i.i = add nsw i32 %h.1.i.i, -8
  %shl11.i.i = shl i64 %v.addr.1.i.i, 8
  %v.addr.2.i.i = select i1 %tobool8.not.i.i, i64 %shl11.i.i, i64 %v.addr.1.i.i
  %h.2.i.i = select i1 %tobool8.not.i.i, i32 %sub10.i.i, i32 %h.1.i.i
  %tobool14.not.i.i = icmp ult i64 %v.addr.2.i.i, 1152921504606846976
  %sub16.i.i = add nsw i32 %h.2.i.i, -4
  %shl17.i.i = shl i64 %v.addr.2.i.i, 4
  %v.addr.3.i.i = select i1 %tobool14.not.i.i, i64 %shl17.i.i, i64 %v.addr.2.i.i
  %h.3.i.i = select i1 %tobool14.not.i.i, i32 %sub16.i.i, i32 %h.2.i.i
  %tobool20.not.i.i = icmp ult i64 %v.addr.3.i.i, 4611686018427387904
  %sub22.i.i = add nsw i32 %h.3.i.i, -2
  %shl23.i.i = shl i64 %v.addr.3.i.i, 2
  %v.addr.4.i.i = select i1 %tobool20.not.i.i, i64 %shl23.i.i, i64 %v.addr.3.i.i
  %h.4.i.i = select i1 %tobool20.not.i.i, i32 %sub22.i.i, i32 %h.3.i.i
  %v.addr.4.lobit.i.i = ashr i64 %v.addr.4.i.i, 63
  %2 = trunc i64 %v.addr.4.lobit.i.i to i32
  %.not.i.i = xor i32 %2, -1
  %spec.select48.i.i = add nuw nsw i32 %h.4.i.i, %i.013.lcssa.i
  %add.i = add i32 %spec.select48.i.i, %.not.i.i
  br label %bits256.exit

for.inc.1.i:                                      ; preds = %for.inc.i
  %tobool.not.2.i = icmp eq i64 %dividend.sroa.9.0.extract.trunc, 0
  br i1 %tobool.not.2.i, label %for.inc.2.i, label %cleanup.i

for.inc.2.i:                                      ; preds = %for.inc.1.i
  %tobool.not.3.i = icmp eq i64 %dividend.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.3.i, label %bits256.exit, label %cleanup.i

bits256.exit:                                     ; preds = %cleanup.i, %for.inc.2.i
  %3 = phi i32 [ %add.i, %cleanup.i ], [ 0, %for.inc.2.i ]
  %tobool.not.i135 = icmp eq i64 %divisor.sroa.10.0.extract.trunc, 0
  br i1 %tobool.not.i135, label %for.inc.i138, label %cleanup.i169

for.inc.i138:                                     ; preds = %bits256.exit
  %tobool.not.1.i137 = icmp eq i64 %divisor.sroa.8.0.extract.trunc, 0
  br i1 %tobool.not.1.i137, label %for.inc.1.i172, label %cleanup.i169

cleanup.i169:                                     ; preds = %for.inc.2.i174, %for.inc.1.i172, %for.inc.i138, %bits256.exit
  %i.013.lcssa.i139 = phi i32 [ 192, %bits256.exit ], [ 128, %for.inc.i138 ], [ 64, %for.inc.1.i172 ], [ 0, %for.inc.2.i174 ]
  %.lcssa.i140 = phi i64 [ %divisor.sroa.10.0.extract.trunc, %bits256.exit ], [ %divisor.sroa.8.0.extract.trunc, %for.inc.i138 ], [ %divisor.sroa.6.0.extract.trunc, %for.inc.1.i172 ], [ %divisor.sroa.0.0.extract.trunc, %for.inc.2.i174 ]
  %tobool.not.i.i141 = icmp ult i64 %.lcssa.i140, 4294967296
  %shl.i.i142 = shl i64 %.lcssa.i140, 32
  %spec.select.i.i143 = select i1 %tobool.not.i.i141, i64 %shl.i.i142, i64 %.lcssa.i140
  %spec.select47.i.i144 = select i1 %tobool.not.i.i141, i32 31, i32 63
  %tobool2.not.i.i145 = icmp ult i64 %spec.select.i.i143, 281474976710656
  %sub4.i.i146 = add nsw i32 %spec.select47.i.i144, -16
  %shl5.i.i147 = shl i64 %spec.select.i.i143, 16
  %v.addr.1.i.i148 = select i1 %tobool2.not.i.i145, i64 %shl5.i.i147, i64 %spec.select.i.i143
  %h.1.i.i149 = select i1 %tobool2.not.i.i145, i32 %sub4.i.i146, i32 %spec.select47.i.i144
  %tobool8.not.i.i150 = icmp ult i64 %v.addr.1.i.i148, 72057594037927936
  %sub10.i.i151 = add nsw i32 %h.1.i.i149, -8
  %shl11.i.i152 = shl i64 %v.addr.1.i.i148, 8
  %v.addr.2.i.i153 = select i1 %tobool8.not.i.i150, i64 %shl11.i.i152, i64 %v.addr.1.i.i148
  %h.2.i.i154 = select i1 %tobool8.not.i.i150, i32 %sub10.i.i151, i32 %h.1.i.i149
  %tobool14.not.i.i155 = icmp ult i64 %v.addr.2.i.i153, 1152921504606846976
  %sub16.i.i156 = add nsw i32 %h.2.i.i154, -4
  %shl17.i.i157 = shl i64 %v.addr.2.i.i153, 4
  %v.addr.3.i.i158 = select i1 %tobool14.not.i.i155, i64 %shl17.i.i157, i64 %v.addr.2.i.i153
  %h.3.i.i159 = select i1 %tobool14.not.i.i155, i32 %sub16.i.i156, i32 %h.2.i.i154
  %tobool20.not.i.i160 = icmp ult i64 %v.addr.3.i.i158, 4611686018427387904
  %sub22.i.i161 = add nsw i32 %h.3.i.i159, -2
  %shl23.i.i162 = shl i64 %v.addr.3.i.i158, 2
  %v.addr.4.i.i163 = select i1 %tobool20.not.i.i160, i64 %shl23.i.i162, i64 %v.addr.3.i.i158
  %h.4.i.i164 = select i1 %tobool20.not.i.i160, i32 %sub22.i.i161, i32 %h.3.i.i159
  %v.addr.4.lobit.i.i165 = ashr i64 %v.addr.4.i.i163, 63
  %4 = trunc i64 %v.addr.4.lobit.i.i165 to i32
  %.not.i.i166 = xor i32 %4, -1
  %spec.select48.i.i167 = add nuw nsw i32 %h.4.i.i164, %i.013.lcssa.i139
  %add.i168 = add i32 %spec.select48.i.i167, %.not.i.i166
  br label %bits256.exit175

for.inc.1.i172:                                   ; preds = %for.inc.i138
  %tobool.not.2.i171 = icmp eq i64 %divisor.sroa.6.0.extract.trunc, 0
  br i1 %tobool.not.2.i171, label %for.inc.2.i174, label %cleanup.i169

for.inc.2.i174:                                   ; preds = %for.inc.1.i172
  %tobool.not.3.i173 = icmp eq i64 %divisor.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.3.i173, label %bits256.exit175, label %cleanup.i169

bits256.exit175:                                  ; preds = %cleanup.i169, %for.inc.2.i174
  %5 = phi i32 [ %add.i168, %cleanup.i169 ], [ 0, %for.inc.2.i174 ]
  %sub = sub nsw i32 %3, %5
  %sh_prom = zext i32 %sub to i256
  %shl = shl i256 %1, %sh_prom
  br i1 %tobool.not.i, label %for.inc.i96, label %cleanup.i127

for.inc.i96:                                      ; preds = %bits256.exit175
  %tobool.not.1.i95 = icmp eq i64 %dividend.sroa.11.0.extract.trunc, 0
  br i1 %tobool.not.1.i95, label %for.inc.1.i130, label %cleanup.i127

cleanup.i127:                                     ; preds = %for.inc.2.i132, %for.inc.1.i130, %for.inc.i96, %bits256.exit175
  %i.013.lcssa.i97 = phi i32 [ 192, %bits256.exit175 ], [ 128, %for.inc.i96 ], [ 64, %for.inc.1.i130 ], [ 0, %for.inc.2.i132 ]
  %.lcssa.i98 = phi i64 [ %dividend.sroa.13.0.extract.trunc, %bits256.exit175 ], [ %dividend.sroa.11.0.extract.trunc, %for.inc.i96 ], [ %dividend.sroa.9.0.extract.trunc, %for.inc.1.i130 ], [ %dividend.sroa.0.0.extract.trunc, %for.inc.2.i132 ]
  %tobool.not.i.i99 = icmp ult i64 %.lcssa.i98, 4294967296
  %shl.i.i100 = shl i64 %.lcssa.i98, 32
  %spec.select.i.i101 = select i1 %tobool.not.i.i99, i64 %shl.i.i100, i64 %.lcssa.i98
  %spec.select47.i.i102 = select i1 %tobool.not.i.i99, i32 31, i32 63
  %tobool2.not.i.i103 = icmp ult i64 %spec.select.i.i101, 281474976710656
  %sub4.i.i104 = add nsw i32 %spec.select47.i.i102, -16
  %shl5.i.i105 = shl i64 %spec.select.i.i101, 16
  %v.addr.1.i.i106 = select i1 %tobool2.not.i.i103, i64 %shl5.i.i105, i64 %spec.select.i.i101
  %h.1.i.i107 = select i1 %tobool2.not.i.i103, i32 %sub4.i.i104, i32 %spec.select47.i.i102
  %tobool8.not.i.i108 = icmp ult i64 %v.addr.1.i.i106, 72057594037927936
  %sub10.i.i109 = add nsw i32 %h.1.i.i107, -8
  %shl11.i.i110 = shl i64 %v.addr.1.i.i106, 8
  %v.addr.2.i.i111 = select i1 %tobool8.not.i.i108, i64 %shl11.i.i110, i64 %v.addr.1.i.i106
  %h.2.i.i112 = select i1 %tobool8.not.i.i108, i32 %sub10.i.i109, i32 %h.1.i.i107
  %tobool14.not.i.i113 = icmp ult i64 %v.addr.2.i.i111, 1152921504606846976
  %sub16.i.i114 = add nsw i32 %h.2.i.i112, -4
  %shl17.i.i115 = shl i64 %v.addr.2.i.i111, 4
  %v.addr.3.i.i116 = select i1 %tobool14.not.i.i113, i64 %shl17.i.i115, i64 %v.addr.2.i.i111
  %h.3.i.i117 = select i1 %tobool14.not.i.i113, i32 %sub16.i.i114, i32 %h.2.i.i112
  %tobool20.not.i.i118 = icmp ult i64 %v.addr.3.i.i116, 4611686018427387904
  %sub22.i.i119 = add nsw i32 %h.3.i.i117, -2
  %shl23.i.i120 = shl i64 %v.addr.3.i.i116, 2
  %v.addr.4.i.i121 = select i1 %tobool20.not.i.i118, i64 %shl23.i.i120, i64 %v.addr.3.i.i116
  %h.4.i.i122 = select i1 %tobool20.not.i.i118, i32 %sub22.i.i119, i32 %h.3.i.i117
  %v.addr.4.lobit.i.i123 = ashr i64 %v.addr.4.i.i121, 63
  %6 = trunc i64 %v.addr.4.lobit.i.i123 to i32
  %.not.i.i124 = xor i32 %6, -1
  %spec.select48.i.i125 = add nuw nsw i32 %h.4.i.i122, %i.013.lcssa.i97
  %add.i126 = add i32 %spec.select48.i.i125, %.not.i.i124
  br label %bits256.exit133

for.inc.1.i130:                                   ; preds = %for.inc.i96
  %tobool.not.2.i129 = icmp eq i64 %dividend.sroa.9.0.extract.trunc, 0
  br i1 %tobool.not.2.i129, label %for.inc.2.i132, label %cleanup.i127

for.inc.2.i132:                                   ; preds = %for.inc.1.i130
  %tobool.not.3.i131 = icmp eq i64 %dividend.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.3.i131, label %bits256.exit133, label %cleanup.i127

bits256.exit133:                                  ; preds = %cleanup.i127, %for.inc.2.i132
  %7 = phi i32 [ %add.i126, %cleanup.i127 ], [ 0, %for.inc.2.i132 ]
  br i1 %tobool.not.i135, label %for.inc.i54, label %cleanup.i85

for.inc.i54:                                      ; preds = %bits256.exit133
  %tobool.not.1.i53 = icmp eq i64 %divisor.sroa.8.0.extract.trunc, 0
  br i1 %tobool.not.1.i53, label %for.inc.1.i88, label %cleanup.i85

cleanup.i85:                                      ; preds = %for.inc.2.i90, %for.inc.1.i88, %for.inc.i54, %bits256.exit133
  %i.013.lcssa.i55 = phi i32 [ 192, %bits256.exit133 ], [ 128, %for.inc.i54 ], [ 64, %for.inc.1.i88 ], [ 0, %for.inc.2.i90 ]
  %.lcssa.i56 = phi i64 [ %divisor.sroa.10.0.extract.trunc, %bits256.exit133 ], [ %divisor.sroa.8.0.extract.trunc, %for.inc.i54 ], [ %divisor.sroa.6.0.extract.trunc, %for.inc.1.i88 ], [ %divisor.sroa.0.0.extract.trunc, %for.inc.2.i90 ]
  %tobool.not.i.i57 = icmp ult i64 %.lcssa.i56, 4294967296
  %shl.i.i58 = shl i64 %.lcssa.i56, 32
  %spec.select.i.i59 = select i1 %tobool.not.i.i57, i64 %shl.i.i58, i64 %.lcssa.i56
  %spec.select47.i.i60 = select i1 %tobool.not.i.i57, i32 31, i32 63
  %tobool2.not.i.i61 = icmp ult i64 %spec.select.i.i59, 281474976710656
  %sub4.i.i62 = add nsw i32 %spec.select47.i.i60, -16
  %shl5.i.i63 = shl i64 %spec.select.i.i59, 16
  %v.addr.1.i.i64 = select i1 %tobool2.not.i.i61, i64 %shl5.i.i63, i64 %spec.select.i.i59
  %h.1.i.i65 = select i1 %tobool2.not.i.i61, i32 %sub4.i.i62, i32 %spec.select47.i.i60
  %tobool8.not.i.i66 = icmp ult i64 %v.addr.1.i.i64, 72057594037927936
  %sub10.i.i67 = add nsw i32 %h.1.i.i65, -8
  %shl11.i.i68 = shl i64 %v.addr.1.i.i64, 8
  %v.addr.2.i.i69 = select i1 %tobool8.not.i.i66, i64 %shl11.i.i68, i64 %v.addr.1.i.i64
  %h.2.i.i70 = select i1 %tobool8.not.i.i66, i32 %sub10.i.i67, i32 %h.1.i.i65
  %tobool14.not.i.i71 = icmp ult i64 %v.addr.2.i.i69, 1152921504606846976
  %sub16.i.i72 = add nsw i32 %h.2.i.i70, -4
  %shl17.i.i73 = shl i64 %v.addr.2.i.i69, 4
  %v.addr.3.i.i74 = select i1 %tobool14.not.i.i71, i64 %shl17.i.i73, i64 %v.addr.2.i.i69
  %h.3.i.i75 = select i1 %tobool14.not.i.i71, i32 %sub16.i.i72, i32 %h.2.i.i70
  %tobool20.not.i.i76 = icmp ult i64 %v.addr.3.i.i74, 4611686018427387904
  %sub22.i.i77 = add nsw i32 %h.3.i.i75, -2
  %shl23.i.i78 = shl i64 %v.addr.3.i.i74, 2
  %v.addr.4.i.i79 = select i1 %tobool20.not.i.i76, i64 %shl23.i.i78, i64 %v.addr.3.i.i74
  %h.4.i.i80 = select i1 %tobool20.not.i.i76, i32 %sub22.i.i77, i32 %h.3.i.i75
  %v.addr.4.lobit.i.i81 = ashr i64 %v.addr.4.i.i79, 63
  %8 = trunc i64 %v.addr.4.lobit.i.i81 to i32
  %.not.i.i82 = xor i32 %8, -1
  %spec.select48.i.i83 = add nuw nsw i32 %h.4.i.i80, %i.013.lcssa.i55
  %add.i84 = add i32 %spec.select48.i.i83, %.not.i.i82
  br label %while.body.preheader

for.inc.1.i88:                                    ; preds = %for.inc.i54
  %tobool.not.2.i87 = icmp eq i64 %divisor.sroa.6.0.extract.trunc, 0
  br i1 %tobool.not.2.i87, label %for.inc.2.i90, label %cleanup.i85

for.inc.2.i90:                                    ; preds = %for.inc.1.i88
  %tobool.not.3.i89 = icmp eq i64 %divisor.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.3.i89, label %while.body.preheader, label %cleanup.i85

while.body.preheader:                             ; preds = %for.inc.2.i90, %cleanup.i85
  %9 = phi i32 [ %add.i84, %cleanup.i85 ], [ 0, %for.inc.2.i90 ]
  %cmp17 = icmp ugt i256 %shl, %0
  %shr = zext i1 %cmp17 to i256
  %sub14 = sub nsw i32 %7, %9
  %sh_prom15 = zext i32 %sub14 to i256
  %shl16 = shl nuw i256 1, %sh_prom15
  %adder.0 = lshr i256 %shl16, %shr
  %copyd.0 = lshr i256 %shl, %shr
  br label %while.body

while.body:                                       ; preds = %while.body.preheader, %while.body
  %adder.1255 = phi i256 [ %shr27, %while.body ], [ %adder.0, %while.body.preheader ]
  %copyd.1254 = phi i256 [ %shr26, %while.body ], [ %copyd.0, %while.body.preheader ]
  %r.0253 = phi i256 [ %r.1, %while.body ], [ %0, %while.body.preheader ]
  %q.0252 = phi i256 [ %q.1, %while.body ], [ 0, %while.body.preheader ]
  %cmp22.not = icmp ult i256 %r.0253, %copyd.1254
  %or = select i1 %cmp22.not, i256 0, i256 %adder.1255
  %q.1 = or i256 %or, %q.0252
  %sub24 = select i1 %cmp22.not, i256 0, i256 %copyd.1254
  %r.1 = sub i256 %r.0253, %sub24
  %shr26 = lshr i256 %copyd.1254, 1
  %shr27 = lshr i256 %adder.1255, 1
  %cmp21.not = icmp ult i256 %r.1, %1
  br i1 %cmp21.not, label %while.end, label %while.body

while.end:                                        ; preds = %while.body
  store i256 %q.1, i256* %quotient, align 8, !tbaa !50
  store i256 %r.1, i256* %remainder, align 8, !tbaa !50
  br label %cleanup

cleanup:                                          ; preds = %entry, %while.end, %if.then9, %if.then5, %if.then2
  %retval.0 = phi i32 [ 0, %if.then2 ], [ 0, %if.then5 ], [ 0, %if.then9 ], [ 0, %while.end ], [ 1, %entry ]
  ret i32 %retval.0
}

; Function Attrs: nounwind
define hidden i32 @sdivmod256(i256* nocapture %pdividend, i256* nocapture %pdivisor, i256* nocapture %remainder, i256* nocapture %quotient) local_unnamed_addr #9 {
entry:
  %0 = bitcast i256* %pdividend to i8*
  %arrayidx = getelementptr inbounds i8, i8* %0, i32 31
  %1 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %cmp = icmp slt i8 %1, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %2 = load i256, i256* %pdividend, align 8, !tbaa !50
  %sub = sub i256 0, %2
  store i256 %sub, i256* %pdividend, align 8, !tbaa !50
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %3 = bitcast i256* %pdivisor to i8*
  %arrayidx2 = getelementptr inbounds i8, i8* %3, i32 31
  %4 = load i8, i8* %arrayidx2, align 1, !tbaa !12
  %cmp4 = icmp slt i8 %4, 0
  br i1 %cmp4, label %if.then8, label %if.end10

if.then8:                                         ; preds = %if.end
  %5 = load i256, i256* %pdivisor, align 8, !tbaa !50
  %sub9 = sub i256 0, %5
  store i256 %sub9, i256* %pdivisor, align 8, !tbaa !50
  br label %if.end10

if.end10:                                         ; preds = %if.then8, %if.end
  %call = tail call i32 @udivmod256(i256* nonnull %pdividend, i256* nonnull %pdivisor, i256* %remainder, i256* %quotient) #18
  %tobool11.not = icmp eq i32 %call, 0
  br i1 %tobool11.not, label %if.end13, label %cleanup

if.end13:                                         ; preds = %if.end10
  %cmp18.not.unshifted = xor i8 %4, %1
  %cmp18.not = icmp sgt i8 %cmp18.not.unshifted, -1
  br i1 %cmp18.not, label %if.end22, label %if.then20

if.then20:                                        ; preds = %if.end13
  %6 = load i256, i256* %quotient, align 8, !tbaa !50
  %sub21 = sub i256 0, %6
  store i256 %sub21, i256* %quotient, align 8, !tbaa !50
  br label %if.end22

if.end22:                                         ; preds = %if.end13, %if.then20
  br i1 %cmp, label %if.then24, label %cleanup

if.then24:                                        ; preds = %if.end22
  %7 = load i256, i256* %remainder, align 8, !tbaa !50
  %sub25 = sub i256 0, %7
  store i256 %sub25, i256* %remainder, align 8, !tbaa !50
  br label %cleanup

cleanup:                                          ; preds = %if.end22, %if.then24, %if.end10
  %retval.0 = phi i32 [ 1, %if.end10 ], [ 0, %if.then24 ], [ 0, %if.end22 ]
  ret i32 %retval.0
}

; Function Attrs: norecurse nounwind readonly
define hidden i32 @bits512(i512* nocapture readonly %value) local_unnamed_addr #13 {
entry:
  %0 = bitcast i512* %value to i64*
  %arrayidx = getelementptr inbounds i64, i64* %0, i32 7
  %1 = load i64, i64* %arrayidx, align 8, !tbaa !4
  %tobool.not = icmp eq i64 %1, 0
  br i1 %tobool.not, label %for.inc, label %cleanup

for.inc:                                          ; preds = %entry
  %arrayidx.1 = getelementptr inbounds i64, i64* %0, i32 6
  %2 = load i64, i64* %arrayidx.1, align 8, !tbaa !4
  %tobool.not.1 = icmp eq i64 %2, 0
  br i1 %tobool.not.1, label %for.inc.1, label %cleanup

cleanup:                                          ; preds = %for.inc.6, %for.inc.5, %for.inc.4, %for.inc.3, %for.inc.2, %for.inc.1, %for.inc, %entry
  %i.013.lcssa = phi i32 [ 448, %entry ], [ 384, %for.inc ], [ 320, %for.inc.1 ], [ 256, %for.inc.2 ], [ 192, %for.inc.3 ], [ 128, %for.inc.4 ], [ 64, %for.inc.5 ], [ 0, %for.inc.6 ]
  %.lcssa = phi i64 [ %1, %entry ], [ %2, %for.inc ], [ %5, %for.inc.1 ], [ %6, %for.inc.2 ], [ %7, %for.inc.3 ], [ %8, %for.inc.4 ], [ %9, %for.inc.5 ], [ %10, %for.inc.6 ]
  %tobool.not.i = icmp ult i64 %.lcssa, 4294967296
  %shl.i = shl i64 %.lcssa, 32
  %spec.select.i = select i1 %tobool.not.i, i64 %shl.i, i64 %.lcssa
  %spec.select47.i = select i1 %tobool.not.i, i32 31, i32 63
  %tobool2.not.i = icmp ult i64 %spec.select.i, 281474976710656
  %sub4.i = add nsw i32 %spec.select47.i, -16
  %shl5.i = shl i64 %spec.select.i, 16
  %v.addr.1.i = select i1 %tobool2.not.i, i64 %shl5.i, i64 %spec.select.i
  %h.1.i = select i1 %tobool2.not.i, i32 %sub4.i, i32 %spec.select47.i
  %tobool8.not.i = icmp ult i64 %v.addr.1.i, 72057594037927936
  %sub10.i = add nsw i32 %h.1.i, -8
  %shl11.i = shl i64 %v.addr.1.i, 8
  %v.addr.2.i = select i1 %tobool8.not.i, i64 %shl11.i, i64 %v.addr.1.i
  %h.2.i = select i1 %tobool8.not.i, i32 %sub10.i, i32 %h.1.i
  %tobool14.not.i = icmp ult i64 %v.addr.2.i, 1152921504606846976
  %sub16.i = add nsw i32 %h.2.i, -4
  %shl17.i = shl i64 %v.addr.2.i, 4
  %v.addr.3.i = select i1 %tobool14.not.i, i64 %shl17.i, i64 %v.addr.2.i
  %h.3.i = select i1 %tobool14.not.i, i32 %sub16.i, i32 %h.2.i
  %tobool20.not.i = icmp ult i64 %v.addr.3.i, 4611686018427387904
  %sub22.i = add nsw i32 %h.3.i, -2
  %shl23.i = shl i64 %v.addr.3.i, 2
  %v.addr.4.i = select i1 %tobool20.not.i, i64 %shl23.i, i64 %v.addr.3.i
  %h.4.i = select i1 %tobool20.not.i, i32 %sub22.i, i32 %h.3.i
  %v.addr.4.lobit.i = ashr i64 %v.addr.4.i, 63
  %3 = trunc i64 %v.addr.4.lobit.i to i32
  %.not.i = xor i32 %3, -1
  %spec.select48.i = add nuw nsw i32 %h.4.i, %i.013.lcssa
  %add = add i32 %spec.select48.i, %.not.i
  br label %.loopexit

.loopexit:                                        ; preds = %for.inc.6, %cleanup
  %4 = phi i32 [ %add, %cleanup ], [ 0, %for.inc.6 ]
  ret i32 %4

for.inc.1:                                        ; preds = %for.inc
  %arrayidx.2 = getelementptr inbounds i64, i64* %0, i32 5
  %5 = load i64, i64* %arrayidx.2, align 8, !tbaa !4
  %tobool.not.2 = icmp eq i64 %5, 0
  br i1 %tobool.not.2, label %for.inc.2, label %cleanup

for.inc.2:                                        ; preds = %for.inc.1
  %arrayidx.3 = getelementptr inbounds i64, i64* %0, i32 4
  %6 = load i64, i64* %arrayidx.3, align 8, !tbaa !4
  %tobool.not.3 = icmp eq i64 %6, 0
  br i1 %tobool.not.3, label %for.inc.3, label %cleanup

for.inc.3:                                        ; preds = %for.inc.2
  %arrayidx.4 = getelementptr inbounds i64, i64* %0, i32 3
  %7 = load i64, i64* %arrayidx.4, align 8, !tbaa !4
  %tobool.not.4 = icmp eq i64 %7, 0
  br i1 %tobool.not.4, label %for.inc.4, label %cleanup

for.inc.4:                                        ; preds = %for.inc.3
  %arrayidx.5 = getelementptr inbounds i64, i64* %0, i32 2
  %8 = load i64, i64* %arrayidx.5, align 8, !tbaa !4
  %tobool.not.5 = icmp eq i64 %8, 0
  br i1 %tobool.not.5, label %for.inc.5, label %cleanup

for.inc.5:                                        ; preds = %for.inc.4
  %arrayidx.6 = getelementptr inbounds i64, i64* %0, i32 1
  %9 = load i64, i64* %arrayidx.6, align 8, !tbaa !4
  %tobool.not.6 = icmp eq i64 %9, 0
  br i1 %tobool.not.6, label %for.inc.6, label %cleanup

for.inc.6:                                        ; preds = %for.inc.5
  %10 = load i64, i64* %0, align 8, !tbaa !4
  %tobool.not.7 = icmp eq i64 %10, 0
  br i1 %tobool.not.7, label %.loopexit, label %cleanup
}

; Function Attrs: nounwind
define hidden i32 @udivmod512(i512* nocapture readonly %pdividend, i512* nocapture readonly %pdivisor, i512* nocapture %remainder, i512* nocapture %quotient) local_unnamed_addr #9 {
entry:
  %0 = load i512, i512* %pdividend, align 8, !tbaa !52
  %dividend.sroa.0.0.extract.trunc = trunc i512 %0 to i64
  %dividend.sroa.9.0.extract.shift = lshr i512 %0, 64
  %dividend.sroa.9.0.extract.trunc = trunc i512 %dividend.sroa.9.0.extract.shift to i64
  %dividend.sroa.11.0.extract.shift = lshr i512 %0, 128
  %dividend.sroa.11.0.extract.trunc = trunc i512 %dividend.sroa.11.0.extract.shift to i64
  %dividend.sroa.13.0.extract.shift = lshr i512 %0, 192
  %dividend.sroa.13.0.extract.trunc = trunc i512 %dividend.sroa.13.0.extract.shift to i64
  %dividend.sroa.15.0.extract.shift = lshr i512 %0, 256
  %dividend.sroa.15.0.extract.trunc = trunc i512 %dividend.sroa.15.0.extract.shift to i64
  %dividend.sroa.17.0.extract.shift = lshr i512 %0, 320
  %dividend.sroa.17.0.extract.trunc = trunc i512 %dividend.sroa.17.0.extract.shift to i64
  %dividend.sroa.19.0.extract.shift = lshr i512 %0, 384
  %dividend.sroa.19.0.extract.trunc = trunc i512 %dividend.sroa.19.0.extract.shift to i64
  %dividend.sroa.21.0.extract.shift = lshr i512 %0, 448
  %dividend.sroa.21.0.extract.trunc = trunc i512 %dividend.sroa.21.0.extract.shift to i64
  %1 = load i512, i512* %pdivisor, align 8, !tbaa !52
  %divisor.sroa.0.0.extract.trunc = trunc i512 %1 to i64
  %divisor.sroa.6.0.extract.shift = lshr i512 %1, 64
  %divisor.sroa.6.0.extract.trunc = trunc i512 %divisor.sroa.6.0.extract.shift to i64
  %divisor.sroa.8.0.extract.shift = lshr i512 %1, 128
  %divisor.sroa.8.0.extract.trunc = trunc i512 %divisor.sroa.8.0.extract.shift to i64
  %divisor.sroa.10.0.extract.shift = lshr i512 %1, 192
  %divisor.sroa.10.0.extract.trunc = trunc i512 %divisor.sroa.10.0.extract.shift to i64
  %divisor.sroa.12.0.extract.shift = lshr i512 %1, 256
  %divisor.sroa.12.0.extract.trunc = trunc i512 %divisor.sroa.12.0.extract.shift to i64
  %divisor.sroa.14.0.extract.shift = lshr i512 %1, 320
  %divisor.sroa.14.0.extract.trunc = trunc i512 %divisor.sroa.14.0.extract.shift to i64
  %divisor.sroa.16.0.extract.shift = lshr i512 %1, 384
  %divisor.sroa.16.0.extract.trunc = trunc i512 %divisor.sroa.16.0.extract.shift to i64
  %divisor.sroa.18.0.extract.shift = lshr i512 %1, 448
  %divisor.sroa.18.0.extract.trunc = trunc i512 %divisor.sroa.18.0.extract.shift to i64
  switch i512 %1, label %if.end3 [
    i512 0, label %cleanup
    i512 1, label %if.then2
  ]

if.then2:                                         ; preds = %entry
  store i512 0, i512* %remainder, align 8, !tbaa !52
  store i512 %0, i512* %quotient, align 8, !tbaa !52
  br label %cleanup

if.end3:                                          ; preds = %entry
  %cmp4 = icmp eq i512 %1, %0
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %if.end3
  store i512 0, i512* %remainder, align 8, !tbaa !52
  store i512 1, i512* %quotient, align 8, !tbaa !52
  br label %cleanup

if.end6:                                          ; preds = %if.end3
  %cmp7 = icmp eq i512 %0, 0
  %cmp8 = icmp ult i512 %0, %1
  %or.cond = or i1 %cmp7, %cmp8
  br i1 %or.cond, label %if.then9, label %if.end10

if.then9:                                         ; preds = %if.end6
  store i512 %0, i512* %remainder, align 8, !tbaa !52
  store i512 0, i512* %quotient, align 8, !tbaa !52
  br label %cleanup

if.end10:                                         ; preds = %if.end6
  %tobool.not.i = icmp eq i64 %dividend.sroa.21.0.extract.trunc, 0
  br i1 %tobool.not.i, label %for.inc.i, label %cleanup.i

for.inc.i:                                        ; preds = %if.end10
  %tobool.not.1.i = icmp eq i64 %dividend.sroa.19.0.extract.trunc, 0
  br i1 %tobool.not.1.i, label %for.inc.1.i, label %cleanup.i

cleanup.i:                                        ; preds = %for.inc.6.i, %for.inc.5.i, %for.inc.4.i, %for.inc.3.i, %for.inc.2.i, %for.inc.1.i, %for.inc.i, %if.end10
  %i.013.lcssa.i = phi i32 [ 448, %if.end10 ], [ 384, %for.inc.i ], [ 320, %for.inc.1.i ], [ 256, %for.inc.2.i ], [ 192, %for.inc.3.i ], [ 128, %for.inc.4.i ], [ 64, %for.inc.5.i ], [ 0, %for.inc.6.i ]
  %.lcssa.i = phi i64 [ %dividend.sroa.21.0.extract.trunc, %if.end10 ], [ %dividend.sroa.19.0.extract.trunc, %for.inc.i ], [ %dividend.sroa.17.0.extract.trunc, %for.inc.1.i ], [ %dividend.sroa.15.0.extract.trunc, %for.inc.2.i ], [ %dividend.sroa.13.0.extract.trunc, %for.inc.3.i ], [ %dividend.sroa.11.0.extract.trunc, %for.inc.4.i ], [ %dividend.sroa.9.0.extract.trunc, %for.inc.5.i ], [ %dividend.sroa.0.0.extract.trunc, %for.inc.6.i ]
  %tobool.not.i.i = icmp ult i64 %.lcssa.i, 4294967296
  %shl.i.i = shl i64 %.lcssa.i, 32
  %spec.select.i.i = select i1 %tobool.not.i.i, i64 %shl.i.i, i64 %.lcssa.i
  %spec.select47.i.i = select i1 %tobool.not.i.i, i32 31, i32 63
  %tobool2.not.i.i = icmp ult i64 %spec.select.i.i, 281474976710656
  %sub4.i.i = add nsw i32 %spec.select47.i.i, -16
  %shl5.i.i = shl i64 %spec.select.i.i, 16
  %v.addr.1.i.i = select i1 %tobool2.not.i.i, i64 %shl5.i.i, i64 %spec.select.i.i
  %h.1.i.i = select i1 %tobool2.not.i.i, i32 %sub4.i.i, i32 %spec.select47.i.i
  %tobool8.not.i.i = icmp ult i64 %v.addr.1.i.i, 72057594037927936
  %sub10.i.i = add nsw i32 %h.1.i.i, -8
  %shl11.i.i = shl i64 %v.addr.1.i.i, 8
  %v.addr.2.i.i = select i1 %tobool8.not.i.i, i64 %shl11.i.i, i64 %v.addr.1.i.i
  %h.2.i.i = select i1 %tobool8.not.i.i, i32 %sub10.i.i, i32 %h.1.i.i
  %tobool14.not.i.i = icmp ult i64 %v.addr.2.i.i, 1152921504606846976
  %sub16.i.i = add nsw i32 %h.2.i.i, -4
  %shl17.i.i = shl i64 %v.addr.2.i.i, 4
  %v.addr.3.i.i = select i1 %tobool14.not.i.i, i64 %shl17.i.i, i64 %v.addr.2.i.i
  %h.3.i.i = select i1 %tobool14.not.i.i, i32 %sub16.i.i, i32 %h.2.i.i
  %tobool20.not.i.i = icmp ult i64 %v.addr.3.i.i, 4611686018427387904
  %sub22.i.i = add nsw i32 %h.3.i.i, -2
  %shl23.i.i = shl i64 %v.addr.3.i.i, 2
  %v.addr.4.i.i = select i1 %tobool20.not.i.i, i64 %shl23.i.i, i64 %v.addr.3.i.i
  %h.4.i.i = select i1 %tobool20.not.i.i, i32 %sub22.i.i, i32 %h.3.i.i
  %v.addr.4.lobit.i.i = ashr i64 %v.addr.4.i.i, 63
  %2 = trunc i64 %v.addr.4.lobit.i.i to i32
  %.not.i.i = xor i32 %2, -1
  %spec.select48.i.i = add nuw nsw i32 %h.4.i.i, %i.013.lcssa.i
  %add.i = add i32 %spec.select48.i.i, %.not.i.i
  br label %bits512.exit

for.inc.1.i:                                      ; preds = %for.inc.i
  %tobool.not.2.i = icmp eq i64 %dividend.sroa.17.0.extract.trunc, 0
  br i1 %tobool.not.2.i, label %for.inc.2.i, label %cleanup.i

for.inc.2.i:                                      ; preds = %for.inc.1.i
  %tobool.not.3.i = icmp eq i64 %dividend.sroa.15.0.extract.trunc, 0
  br i1 %tobool.not.3.i, label %for.inc.3.i, label %cleanup.i

for.inc.3.i:                                      ; preds = %for.inc.2.i
  %tobool.not.4.i = icmp eq i64 %dividend.sroa.13.0.extract.trunc, 0
  br i1 %tobool.not.4.i, label %for.inc.4.i, label %cleanup.i

for.inc.4.i:                                      ; preds = %for.inc.3.i
  %tobool.not.5.i = icmp eq i64 %dividend.sroa.11.0.extract.trunc, 0
  br i1 %tobool.not.5.i, label %for.inc.5.i, label %cleanup.i

for.inc.5.i:                                      ; preds = %for.inc.4.i
  %tobool.not.6.i = icmp eq i64 %dividend.sroa.9.0.extract.trunc, 0
  br i1 %tobool.not.6.i, label %for.inc.6.i, label %cleanup.i

for.inc.6.i:                                      ; preds = %for.inc.5.i
  %tobool.not.7.i = icmp eq i64 %dividend.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.7.i, label %bits512.exit, label %cleanup.i

bits512.exit:                                     ; preds = %cleanup.i, %for.inc.6.i
  %3 = phi i32 [ %add.i, %cleanup.i ], [ 0, %for.inc.6.i ]
  %tobool.not.i159 = icmp eq i64 %divisor.sroa.18.0.extract.trunc, 0
  br i1 %tobool.not.i159, label %for.inc.i162, label %cleanup.i193

for.inc.i162:                                     ; preds = %bits512.exit
  %tobool.not.1.i161 = icmp eq i64 %divisor.sroa.16.0.extract.trunc, 0
  br i1 %tobool.not.1.i161, label %for.inc.1.i196, label %cleanup.i193

cleanup.i193:                                     ; preds = %for.inc.6.i210, %for.inc.5.i208, %for.inc.4.i205, %for.inc.3.i202, %for.inc.2.i199, %for.inc.1.i196, %for.inc.i162, %bits512.exit
  %i.013.lcssa.i163 = phi i32 [ 448, %bits512.exit ], [ 384, %for.inc.i162 ], [ 320, %for.inc.1.i196 ], [ 256, %for.inc.2.i199 ], [ 192, %for.inc.3.i202 ], [ 128, %for.inc.4.i205 ], [ 64, %for.inc.5.i208 ], [ 0, %for.inc.6.i210 ]
  %.lcssa.i164 = phi i64 [ %divisor.sroa.18.0.extract.trunc, %bits512.exit ], [ %divisor.sroa.16.0.extract.trunc, %for.inc.i162 ], [ %divisor.sroa.14.0.extract.trunc, %for.inc.1.i196 ], [ %divisor.sroa.12.0.extract.trunc, %for.inc.2.i199 ], [ %divisor.sroa.10.0.extract.trunc, %for.inc.3.i202 ], [ %divisor.sroa.8.0.extract.trunc, %for.inc.4.i205 ], [ %divisor.sroa.6.0.extract.trunc, %for.inc.5.i208 ], [ %divisor.sroa.0.0.extract.trunc, %for.inc.6.i210 ]
  %tobool.not.i.i165 = icmp ult i64 %.lcssa.i164, 4294967296
  %shl.i.i166 = shl i64 %.lcssa.i164, 32
  %spec.select.i.i167 = select i1 %tobool.not.i.i165, i64 %shl.i.i166, i64 %.lcssa.i164
  %spec.select47.i.i168 = select i1 %tobool.not.i.i165, i32 31, i32 63
  %tobool2.not.i.i169 = icmp ult i64 %spec.select.i.i167, 281474976710656
  %sub4.i.i170 = add nsw i32 %spec.select47.i.i168, -16
  %shl5.i.i171 = shl i64 %spec.select.i.i167, 16
  %v.addr.1.i.i172 = select i1 %tobool2.not.i.i169, i64 %shl5.i.i171, i64 %spec.select.i.i167
  %h.1.i.i173 = select i1 %tobool2.not.i.i169, i32 %sub4.i.i170, i32 %spec.select47.i.i168
  %tobool8.not.i.i174 = icmp ult i64 %v.addr.1.i.i172, 72057594037927936
  %sub10.i.i175 = add nsw i32 %h.1.i.i173, -8
  %shl11.i.i176 = shl i64 %v.addr.1.i.i172, 8
  %v.addr.2.i.i177 = select i1 %tobool8.not.i.i174, i64 %shl11.i.i176, i64 %v.addr.1.i.i172
  %h.2.i.i178 = select i1 %tobool8.not.i.i174, i32 %sub10.i.i175, i32 %h.1.i.i173
  %tobool14.not.i.i179 = icmp ult i64 %v.addr.2.i.i177, 1152921504606846976
  %sub16.i.i180 = add nsw i32 %h.2.i.i178, -4
  %shl17.i.i181 = shl i64 %v.addr.2.i.i177, 4
  %v.addr.3.i.i182 = select i1 %tobool14.not.i.i179, i64 %shl17.i.i181, i64 %v.addr.2.i.i177
  %h.3.i.i183 = select i1 %tobool14.not.i.i179, i32 %sub16.i.i180, i32 %h.2.i.i178
  %tobool20.not.i.i184 = icmp ult i64 %v.addr.3.i.i182, 4611686018427387904
  %sub22.i.i185 = add nsw i32 %h.3.i.i183, -2
  %shl23.i.i186 = shl i64 %v.addr.3.i.i182, 2
  %v.addr.4.i.i187 = select i1 %tobool20.not.i.i184, i64 %shl23.i.i186, i64 %v.addr.3.i.i182
  %h.4.i.i188 = select i1 %tobool20.not.i.i184, i32 %sub22.i.i185, i32 %h.3.i.i183
  %v.addr.4.lobit.i.i189 = ashr i64 %v.addr.4.i.i187, 63
  %4 = trunc i64 %v.addr.4.lobit.i.i189 to i32
  %.not.i.i190 = xor i32 %4, -1
  %spec.select48.i.i191 = add nuw nsw i32 %h.4.i.i188, %i.013.lcssa.i163
  %add.i192 = add i32 %spec.select48.i.i191, %.not.i.i190
  br label %bits512.exit211

for.inc.1.i196:                                   ; preds = %for.inc.i162
  %tobool.not.2.i195 = icmp eq i64 %divisor.sroa.14.0.extract.trunc, 0
  br i1 %tobool.not.2.i195, label %for.inc.2.i199, label %cleanup.i193

for.inc.2.i199:                                   ; preds = %for.inc.1.i196
  %tobool.not.3.i198 = icmp eq i64 %divisor.sroa.12.0.extract.trunc, 0
  br i1 %tobool.not.3.i198, label %for.inc.3.i202, label %cleanup.i193

for.inc.3.i202:                                   ; preds = %for.inc.2.i199
  %tobool.not.4.i201 = icmp eq i64 %divisor.sroa.10.0.extract.trunc, 0
  br i1 %tobool.not.4.i201, label %for.inc.4.i205, label %cleanup.i193

for.inc.4.i205:                                   ; preds = %for.inc.3.i202
  %tobool.not.5.i204 = icmp eq i64 %divisor.sroa.8.0.extract.trunc, 0
  br i1 %tobool.not.5.i204, label %for.inc.5.i208, label %cleanup.i193

for.inc.5.i208:                                   ; preds = %for.inc.4.i205
  %tobool.not.6.i207 = icmp eq i64 %divisor.sroa.6.0.extract.trunc, 0
  br i1 %tobool.not.6.i207, label %for.inc.6.i210, label %cleanup.i193

for.inc.6.i210:                                   ; preds = %for.inc.5.i208
  %tobool.not.7.i209 = icmp eq i64 %divisor.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.7.i209, label %bits512.exit211, label %cleanup.i193

bits512.exit211:                                  ; preds = %cleanup.i193, %for.inc.6.i210
  %5 = phi i32 [ %add.i192, %cleanup.i193 ], [ 0, %for.inc.6.i210 ]
  %sub = sub nsw i32 %3, %5
  %sh_prom = zext i32 %sub to i512
  %shl = shl i512 %1, %sh_prom
  br i1 %tobool.not.i, label %for.inc.i108, label %cleanup.i139

for.inc.i108:                                     ; preds = %bits512.exit211
  %tobool.not.1.i107 = icmp eq i64 %dividend.sroa.19.0.extract.trunc, 0
  br i1 %tobool.not.1.i107, label %for.inc.1.i142, label %cleanup.i139

cleanup.i139:                                     ; preds = %for.inc.6.i156, %for.inc.5.i154, %for.inc.4.i151, %for.inc.3.i148, %for.inc.2.i145, %for.inc.1.i142, %for.inc.i108, %bits512.exit211
  %i.013.lcssa.i109 = phi i32 [ 448, %bits512.exit211 ], [ 384, %for.inc.i108 ], [ 320, %for.inc.1.i142 ], [ 256, %for.inc.2.i145 ], [ 192, %for.inc.3.i148 ], [ 128, %for.inc.4.i151 ], [ 64, %for.inc.5.i154 ], [ 0, %for.inc.6.i156 ]
  %.lcssa.i110 = phi i64 [ %dividend.sroa.21.0.extract.trunc, %bits512.exit211 ], [ %dividend.sroa.19.0.extract.trunc, %for.inc.i108 ], [ %dividend.sroa.17.0.extract.trunc, %for.inc.1.i142 ], [ %dividend.sroa.15.0.extract.trunc, %for.inc.2.i145 ], [ %dividend.sroa.13.0.extract.trunc, %for.inc.3.i148 ], [ %dividend.sroa.11.0.extract.trunc, %for.inc.4.i151 ], [ %dividend.sroa.9.0.extract.trunc, %for.inc.5.i154 ], [ %dividend.sroa.0.0.extract.trunc, %for.inc.6.i156 ]
  %tobool.not.i.i111 = icmp ult i64 %.lcssa.i110, 4294967296
  %shl.i.i112 = shl i64 %.lcssa.i110, 32
  %spec.select.i.i113 = select i1 %tobool.not.i.i111, i64 %shl.i.i112, i64 %.lcssa.i110
  %spec.select47.i.i114 = select i1 %tobool.not.i.i111, i32 31, i32 63
  %tobool2.not.i.i115 = icmp ult i64 %spec.select.i.i113, 281474976710656
  %sub4.i.i116 = add nsw i32 %spec.select47.i.i114, -16
  %shl5.i.i117 = shl i64 %spec.select.i.i113, 16
  %v.addr.1.i.i118 = select i1 %tobool2.not.i.i115, i64 %shl5.i.i117, i64 %spec.select.i.i113
  %h.1.i.i119 = select i1 %tobool2.not.i.i115, i32 %sub4.i.i116, i32 %spec.select47.i.i114
  %tobool8.not.i.i120 = icmp ult i64 %v.addr.1.i.i118, 72057594037927936
  %sub10.i.i121 = add nsw i32 %h.1.i.i119, -8
  %shl11.i.i122 = shl i64 %v.addr.1.i.i118, 8
  %v.addr.2.i.i123 = select i1 %tobool8.not.i.i120, i64 %shl11.i.i122, i64 %v.addr.1.i.i118
  %h.2.i.i124 = select i1 %tobool8.not.i.i120, i32 %sub10.i.i121, i32 %h.1.i.i119
  %tobool14.not.i.i125 = icmp ult i64 %v.addr.2.i.i123, 1152921504606846976
  %sub16.i.i126 = add nsw i32 %h.2.i.i124, -4
  %shl17.i.i127 = shl i64 %v.addr.2.i.i123, 4
  %v.addr.3.i.i128 = select i1 %tobool14.not.i.i125, i64 %shl17.i.i127, i64 %v.addr.2.i.i123
  %h.3.i.i129 = select i1 %tobool14.not.i.i125, i32 %sub16.i.i126, i32 %h.2.i.i124
  %tobool20.not.i.i130 = icmp ult i64 %v.addr.3.i.i128, 4611686018427387904
  %sub22.i.i131 = add nsw i32 %h.3.i.i129, -2
  %shl23.i.i132 = shl i64 %v.addr.3.i.i128, 2
  %v.addr.4.i.i133 = select i1 %tobool20.not.i.i130, i64 %shl23.i.i132, i64 %v.addr.3.i.i128
  %h.4.i.i134 = select i1 %tobool20.not.i.i130, i32 %sub22.i.i131, i32 %h.3.i.i129
  %v.addr.4.lobit.i.i135 = ashr i64 %v.addr.4.i.i133, 63
  %6 = trunc i64 %v.addr.4.lobit.i.i135 to i32
  %.not.i.i136 = xor i32 %6, -1
  %spec.select48.i.i137 = add nuw nsw i32 %h.4.i.i134, %i.013.lcssa.i109
  %add.i138 = add i32 %spec.select48.i.i137, %.not.i.i136
  br label %bits512.exit157

for.inc.1.i142:                                   ; preds = %for.inc.i108
  %tobool.not.2.i141 = icmp eq i64 %dividend.sroa.17.0.extract.trunc, 0
  br i1 %tobool.not.2.i141, label %for.inc.2.i145, label %cleanup.i139

for.inc.2.i145:                                   ; preds = %for.inc.1.i142
  %tobool.not.3.i144 = icmp eq i64 %dividend.sroa.15.0.extract.trunc, 0
  br i1 %tobool.not.3.i144, label %for.inc.3.i148, label %cleanup.i139

for.inc.3.i148:                                   ; preds = %for.inc.2.i145
  %tobool.not.4.i147 = icmp eq i64 %dividend.sroa.13.0.extract.trunc, 0
  br i1 %tobool.not.4.i147, label %for.inc.4.i151, label %cleanup.i139

for.inc.4.i151:                                   ; preds = %for.inc.3.i148
  %tobool.not.5.i150 = icmp eq i64 %dividend.sroa.11.0.extract.trunc, 0
  br i1 %tobool.not.5.i150, label %for.inc.5.i154, label %cleanup.i139

for.inc.5.i154:                                   ; preds = %for.inc.4.i151
  %tobool.not.6.i153 = icmp eq i64 %dividend.sroa.9.0.extract.trunc, 0
  br i1 %tobool.not.6.i153, label %for.inc.6.i156, label %cleanup.i139

for.inc.6.i156:                                   ; preds = %for.inc.5.i154
  %tobool.not.7.i155 = icmp eq i64 %dividend.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.7.i155, label %bits512.exit157, label %cleanup.i139

bits512.exit157:                                  ; preds = %cleanup.i139, %for.inc.6.i156
  %7 = phi i32 [ %add.i138, %cleanup.i139 ], [ 0, %for.inc.6.i156 ]
  br i1 %tobool.not.i159, label %for.inc.i54, label %cleanup.i85

for.inc.i54:                                      ; preds = %bits512.exit157
  %tobool.not.1.i53 = icmp eq i64 %divisor.sroa.16.0.extract.trunc, 0
  br i1 %tobool.not.1.i53, label %for.inc.1.i88, label %cleanup.i85

cleanup.i85:                                      ; preds = %for.inc.6.i102, %for.inc.5.i100, %for.inc.4.i97, %for.inc.3.i94, %for.inc.2.i91, %for.inc.1.i88, %for.inc.i54, %bits512.exit157
  %i.013.lcssa.i55 = phi i32 [ 448, %bits512.exit157 ], [ 384, %for.inc.i54 ], [ 320, %for.inc.1.i88 ], [ 256, %for.inc.2.i91 ], [ 192, %for.inc.3.i94 ], [ 128, %for.inc.4.i97 ], [ 64, %for.inc.5.i100 ], [ 0, %for.inc.6.i102 ]
  %.lcssa.i56 = phi i64 [ %divisor.sroa.18.0.extract.trunc, %bits512.exit157 ], [ %divisor.sroa.16.0.extract.trunc, %for.inc.i54 ], [ %divisor.sroa.14.0.extract.trunc, %for.inc.1.i88 ], [ %divisor.sroa.12.0.extract.trunc, %for.inc.2.i91 ], [ %divisor.sroa.10.0.extract.trunc, %for.inc.3.i94 ], [ %divisor.sroa.8.0.extract.trunc, %for.inc.4.i97 ], [ %divisor.sroa.6.0.extract.trunc, %for.inc.5.i100 ], [ %divisor.sroa.0.0.extract.trunc, %for.inc.6.i102 ]
  %tobool.not.i.i57 = icmp ult i64 %.lcssa.i56, 4294967296
  %shl.i.i58 = shl i64 %.lcssa.i56, 32
  %spec.select.i.i59 = select i1 %tobool.not.i.i57, i64 %shl.i.i58, i64 %.lcssa.i56
  %spec.select47.i.i60 = select i1 %tobool.not.i.i57, i32 31, i32 63
  %tobool2.not.i.i61 = icmp ult i64 %spec.select.i.i59, 281474976710656
  %sub4.i.i62 = add nsw i32 %spec.select47.i.i60, -16
  %shl5.i.i63 = shl i64 %spec.select.i.i59, 16
  %v.addr.1.i.i64 = select i1 %tobool2.not.i.i61, i64 %shl5.i.i63, i64 %spec.select.i.i59
  %h.1.i.i65 = select i1 %tobool2.not.i.i61, i32 %sub4.i.i62, i32 %spec.select47.i.i60
  %tobool8.not.i.i66 = icmp ult i64 %v.addr.1.i.i64, 72057594037927936
  %sub10.i.i67 = add nsw i32 %h.1.i.i65, -8
  %shl11.i.i68 = shl i64 %v.addr.1.i.i64, 8
  %v.addr.2.i.i69 = select i1 %tobool8.not.i.i66, i64 %shl11.i.i68, i64 %v.addr.1.i.i64
  %h.2.i.i70 = select i1 %tobool8.not.i.i66, i32 %sub10.i.i67, i32 %h.1.i.i65
  %tobool14.not.i.i71 = icmp ult i64 %v.addr.2.i.i69, 1152921504606846976
  %sub16.i.i72 = add nsw i32 %h.2.i.i70, -4
  %shl17.i.i73 = shl i64 %v.addr.2.i.i69, 4
  %v.addr.3.i.i74 = select i1 %tobool14.not.i.i71, i64 %shl17.i.i73, i64 %v.addr.2.i.i69
  %h.3.i.i75 = select i1 %tobool14.not.i.i71, i32 %sub16.i.i72, i32 %h.2.i.i70
  %tobool20.not.i.i76 = icmp ult i64 %v.addr.3.i.i74, 4611686018427387904
  %sub22.i.i77 = add nsw i32 %h.3.i.i75, -2
  %shl23.i.i78 = shl i64 %v.addr.3.i.i74, 2
  %v.addr.4.i.i79 = select i1 %tobool20.not.i.i76, i64 %shl23.i.i78, i64 %v.addr.3.i.i74
  %h.4.i.i80 = select i1 %tobool20.not.i.i76, i32 %sub22.i.i77, i32 %h.3.i.i75
  %v.addr.4.lobit.i.i81 = ashr i64 %v.addr.4.i.i79, 63
  %8 = trunc i64 %v.addr.4.lobit.i.i81 to i32
  %.not.i.i82 = xor i32 %8, -1
  %spec.select48.i.i83 = add nuw nsw i32 %h.4.i.i80, %i.013.lcssa.i55
  %add.i84 = add i32 %spec.select48.i.i83, %.not.i.i82
  br label %while.body.preheader

for.inc.1.i88:                                    ; preds = %for.inc.i54
  %tobool.not.2.i87 = icmp eq i64 %divisor.sroa.14.0.extract.trunc, 0
  br i1 %tobool.not.2.i87, label %for.inc.2.i91, label %cleanup.i85

for.inc.2.i91:                                    ; preds = %for.inc.1.i88
  %tobool.not.3.i90 = icmp eq i64 %divisor.sroa.12.0.extract.trunc, 0
  br i1 %tobool.not.3.i90, label %for.inc.3.i94, label %cleanup.i85

for.inc.3.i94:                                    ; preds = %for.inc.2.i91
  %tobool.not.4.i93 = icmp eq i64 %divisor.sroa.10.0.extract.trunc, 0
  br i1 %tobool.not.4.i93, label %for.inc.4.i97, label %cleanup.i85

for.inc.4.i97:                                    ; preds = %for.inc.3.i94
  %tobool.not.5.i96 = icmp eq i64 %divisor.sroa.8.0.extract.trunc, 0
  br i1 %tobool.not.5.i96, label %for.inc.5.i100, label %cleanup.i85

for.inc.5.i100:                                   ; preds = %for.inc.4.i97
  %tobool.not.6.i99 = icmp eq i64 %divisor.sroa.6.0.extract.trunc, 0
  br i1 %tobool.not.6.i99, label %for.inc.6.i102, label %cleanup.i85

for.inc.6.i102:                                   ; preds = %for.inc.5.i100
  %tobool.not.7.i101 = icmp eq i64 %divisor.sroa.0.0.extract.trunc, 0
  br i1 %tobool.not.7.i101, label %while.body.preheader, label %cleanup.i85

while.body.preheader:                             ; preds = %for.inc.6.i102, %cleanup.i85
  %9 = phi i32 [ %add.i84, %cleanup.i85 ], [ 0, %for.inc.6.i102 ]
  %cmp17 = icmp ugt i512 %shl, %0
  %shr = zext i1 %cmp17 to i512
  %sub14 = sub nsw i32 %7, %9
  %sh_prom15 = zext i32 %sub14 to i512
  %shl16 = shl nuw i512 1, %sh_prom15
  %adder.0 = lshr i512 %shl16, %shr
  %copyd.0 = lshr i512 %shl, %shr
  br label %while.body

while.body:                                       ; preds = %while.body.preheader, %while.body
  %adder.1367 = phi i512 [ %shr27, %while.body ], [ %adder.0, %while.body.preheader ]
  %copyd.1366 = phi i512 [ %shr26, %while.body ], [ %copyd.0, %while.body.preheader ]
  %r.0365 = phi i512 [ %r.1, %while.body ], [ %0, %while.body.preheader ]
  %q.0364 = phi i512 [ %q.1, %while.body ], [ 0, %while.body.preheader ]
  %cmp22.not = icmp ult i512 %r.0365, %copyd.1366
  %or = select i1 %cmp22.not, i512 0, i512 %adder.1367
  %q.1 = or i512 %or, %q.0364
  %sub24 = select i1 %cmp22.not, i512 0, i512 %copyd.1366
  %r.1 = sub i512 %r.0365, %sub24
  %shr26 = lshr i512 %copyd.1366, 1
  %shr27 = lshr i512 %adder.1367, 1
  %cmp21.not = icmp ult i512 %r.1, %1
  br i1 %cmp21.not, label %while.end, label %while.body

while.end:                                        ; preds = %while.body
  store i512 %q.1, i512* %quotient, align 8, !tbaa !52
  store i512 %r.1, i512* %remainder, align 8, !tbaa !52
  br label %cleanup

cleanup:                                          ; preds = %entry, %while.end, %if.then9, %if.then5, %if.then2
  %retval.0 = phi i32 [ 0, %if.then2 ], [ 0, %if.then5 ], [ 0, %if.then9 ], [ 0, %while.end ], [ 1, %entry ]
  ret i32 %retval.0
}

; Function Attrs: nounwind
define hidden i32 @sdivmod512(i512* nocapture %pdividend, i512* nocapture %pdivisor, i512* nocapture %remainder, i512* nocapture %quotient) local_unnamed_addr #9 {
entry:
  %0 = bitcast i512* %pdividend to i8*
  %arrayidx = getelementptr inbounds i8, i8* %0, i32 63
  %1 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %cmp = icmp slt i8 %1, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %2 = load i512, i512* %pdividend, align 8, !tbaa !52
  %sub = sub i512 0, %2
  store i512 %sub, i512* %pdividend, align 8, !tbaa !52
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %3 = bitcast i512* %pdivisor to i8*
  %arrayidx2 = getelementptr inbounds i8, i8* %3, i32 63
  %4 = load i8, i8* %arrayidx2, align 1, !tbaa !12
  %cmp4 = icmp slt i8 %4, 0
  br i1 %cmp4, label %if.then8, label %if.end10

if.then8:                                         ; preds = %if.end
  %5 = load i512, i512* %pdivisor, align 8, !tbaa !52
  %sub9 = sub i512 0, %5
  store i512 %sub9, i512* %pdivisor, align 8, !tbaa !52
  br label %if.end10

if.end10:                                         ; preds = %if.then8, %if.end
  %call = tail call i32 @udivmod512(i512* nonnull %pdividend, i512* nonnull %pdivisor, i512* %remainder, i512* %quotient) #18
  %tobool11.not = icmp eq i32 %call, 0
  br i1 %tobool11.not, label %if.end13, label %cleanup

if.end13:                                         ; preds = %if.end10
  %cmp18.not.unshifted = xor i8 %4, %1
  %cmp18.not = icmp sgt i8 %cmp18.not.unshifted, -1
  br i1 %cmp18.not, label %if.end22, label %if.then20

if.then20:                                        ; preds = %if.end13
  %6 = load i512, i512* %quotient, align 8, !tbaa !52
  %sub21 = sub i512 0, %6
  store i512 %sub21, i512* %quotient, align 8, !tbaa !52
  br label %if.end22

if.end22:                                         ; preds = %if.end13, %if.then20
  br i1 %cmp, label %if.then24, label %cleanup

if.then24:                                        ; preds = %if.end22
  %7 = load i512, i512* %remainder, align 8, !tbaa !52
  %sub25 = sub i512 0, %7
  store i512 %sub25, i512* %remainder, align 8, !tbaa !52
  br label %cleanup

cleanup:                                          ; preds = %if.end22, %if.then24, %if.end10
  %retval.0 = phi i32 [ 1, %if.end10 ], [ 0, %if.then24 ], [ 0, %if.end22 ]
  ret i32 %retval.0
}

; Function Attrs: nofree norecurse nounwind
define hidden void @hex_encode(i8* nocapture %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %cmp34.not = icmp eq i32 %length, 0
  br i1 %cmp34.not, label %for.cond.cleanup, label %for.body

for.cond.cleanup:                                 ; preds = %for.body, %entry
  ret void

for.body:                                         ; preds = %entry, %for.body
  %output.addr.036 = phi i8* [ %incdec.ptr25, %for.body ], [ %output, %entry ]
  %i.035 = phi i32 [ %inc, %for.body ], [ 0, %entry ]
  %arrayidx = getelementptr inbounds i8, i8* %input, i32 %i.035
  %0 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %1 = lshr i8 %0, 4
  %cmp3 = icmp ugt i8 %0, -97
  %sub = add nuw nsw i8 %1, 87
  %add7 = or i8 %1, 48
  %cond = select i1 %cmp3, i8 %sub, i8 %add7
  %incdec.ptr = getelementptr inbounds i8, i8* %output.addr.036, i32 1
  store i8 %cond, i8* %output.addr.036, align 1, !tbaa !12
  %2 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %3 = and i8 %2, 15
  %cmp13 = icmp ugt i8 %3, 9
  %sub18 = add nuw nsw i8 %3, 87
  %add21 = or i8 %3, 48
  %cond23 = select i1 %cmp13, i8 %sub18, i8 %add21
  %incdec.ptr25 = getelementptr inbounds i8, i8* %output.addr.036, i32 2
  store i8 %cond23, i8* %incdec.ptr, align 1, !tbaa !12
  %inc = add nuw nsw i32 %i.035, 1
  %exitcond.not = icmp eq i32 %inc, %length
  br i1 %exitcond.not, label %for.cond.cleanup, label %for.body
}

; Function Attrs: nofree norecurse nounwind
define hidden void @hex_encode_rev(i8* nocapture %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %i.035 = add i32 %length, -1
  %cmp36 = icmp sgt i32 %i.035, -1
  br i1 %cmp36, label %for.body, label %for.cond.cleanup

for.cond.cleanup:                                 ; preds = %for.body, %entry
  ret void

for.body:                                         ; preds = %entry, %for.body
  %i.038 = phi i32 [ %i.0, %for.body ], [ %i.035, %entry ]
  %output.addr.037 = phi i8* [ %incdec.ptr26, %for.body ], [ %output, %entry ]
  %arrayidx = getelementptr inbounds i8, i8* %input, i32 %i.038
  %0 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %1 = lshr i8 %0, 4
  %cmp3 = icmp ugt i8 %0, -97
  %sub6 = add nuw nsw i8 %1, 87
  %add8 = or i8 %1, 48
  %cond = select i1 %cmp3, i8 %sub6, i8 %add8
  %incdec.ptr = getelementptr inbounds i8, i8* %output.addr.037, i32 1
  store i8 %cond, i8* %output.addr.037, align 1, !tbaa !12
  %2 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %3 = and i8 %2, 15
  %cmp14 = icmp ugt i8 %3, 9
  %sub19 = add nuw nsw i8 %3, 87
  %add22 = or i8 %3, 48
  %cond24 = select i1 %cmp14, i8 %sub19, i8 %add22
  %incdec.ptr26 = getelementptr inbounds i8, i8* %output.addr.037, i32 2
  store i8 %cond24, i8* %incdec.ptr, align 1, !tbaa !12
  %i.0 = add nsw i32 %i.038, -1
  %cmp = icmp sgt i32 %i.038, 0
  br i1 %cmp, label %for.body, label %for.cond.cleanup
}

; Function Attrs: nofree norecurse nounwind
define hidden nonnull i8* @uint2hex(i8* %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %0 = icmp ne i32 %length, 0
  %umin = zext i1 %0 to i32
  br label %while.cond

while.cond:                                       ; preds = %land.rhs, %entry
  %length.addr.0 = phi i32 [ %length, %entry ], [ %sub, %land.rhs ]
  %cmp = icmp ugt i32 %length.addr.0, 1
  br i1 %cmp, label %land.rhs, label %while.cond.while.end_crit_edge

while.cond.while.end_crit_edge:                   ; preds = %while.cond
  %not. = xor i1 %0, true
  %.pre112 = sext i1 %not. to i32
  br label %while.end

land.rhs:                                         ; preds = %while.cond
  %sub = add i32 %length.addr.0, -1
  %arrayidx = getelementptr inbounds i8, i8* %input, i32 %sub
  %1 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %cmp1 = icmp eq i8 %1, 0
  br i1 %cmp1, label %while.cond, label %while.end

while.end:                                        ; preds = %land.rhs, %while.cond.while.end_crit_edge
  %sub4.pre-phi = phi i32 [ %.pre112, %while.cond.while.end_crit_edge ], [ %sub, %land.rhs ]
  %length.addr.0.lcssa = phi i32 [ %umin, %while.cond.while.end_crit_edge ], [ %length.addr.0, %land.rhs ]
  %incdec.ptr = getelementptr inbounds i8, i8* %output, i32 1
  store i8 48, i8* %output, align 1, !tbaa !12
  %incdec.ptr3 = getelementptr inbounds i8, i8* %output, i32 2
  store i8 120, i8* %incdec.ptr, align 1, !tbaa !12
  %arrayidx5 = getelementptr inbounds i8, i8* %input, i32 %sub4.pre-phi
  %2 = load i8, i8* %arrayidx5, align 1, !tbaa !12
  %3 = lshr i8 %2, 4
  %cmp9.not = icmp eq i8 %3, 0
  br i1 %cmp9.not, label %if.end, label %if.then

if.then:                                          ; preds = %while.end
  %cmp12 = icmp ugt i8 %2, -97
  %sub15 = add nuw nsw i8 %3, 87
  %add17 = or i8 %3, 48
  %cond = select i1 %cmp12, i8 %sub15, i8 %add17
  %incdec.ptr19 = getelementptr inbounds i8, i8* %output, i32 3
  store i8 %cond, i8* %incdec.ptr3, align 1, !tbaa !12
  %.pre = load i8, i8* %arrayidx5, align 1, !tbaa !12
  br label %if.end

if.end:                                           ; preds = %while.end, %if.then
  %4 = phi i8 [ %.pre, %if.then ], [ %2, %while.end ]
  %output.addr.0 = phi i8* [ %incdec.ptr19, %if.then ], [ %incdec.ptr3, %while.end ]
  %5 = and i8 %4, 15
  %cmp25 = icmp ugt i8 %5, 9
  %sub30 = add nuw nsw i8 %5, 87
  %add33 = or i8 %5, 48
  %cond35 = select i1 %cmp25, i8 %sub30, i8 %add33
  store i8 %cond35, i8* %output.addr.0, align 1, !tbaa !12
  %output.addr.1104 = getelementptr inbounds i8, i8* %output.addr.0, i32 1
  %tobool.not106 = icmp eq i32 %sub4.pre-phi, 0
  br i1 %tobool.not106, label %while.end81, label %while.body40

while.body40:                                     ; preds = %if.end, %while.body40
  %dec39110 = phi i32 [ %dec39, %while.body40 ], [ %sub4.pre-phi, %if.end ]
  %output.addr.1109 = phi i8* [ %output.addr.1, %while.body40 ], [ %output.addr.1104, %if.end ]
  %output.addr.0.pn108 = phi i8* [ %incdec.ptr60, %while.body40 ], [ %output.addr.0, %if.end ]
  %length.addr.1107 = phi i32 [ %dec39110, %while.body40 ], [ %length.addr.0.lcssa, %if.end ]
  %sub42 = add i32 %length.addr.1107, -2
  %arrayidx43 = getelementptr inbounds i8, i8* %input, i32 %sub42
  %6 = load i8, i8* %arrayidx43, align 1, !tbaa !12
  %7 = lshr i8 %6, 4
  %cmp48 = icmp ugt i8 %6, -97
  %sub53 = add nuw nsw i8 %7, 87
  %add56 = or i8 %7, 48
  %cond58 = select i1 %cmp48, i8 %sub53, i8 %add56
  %incdec.ptr60 = getelementptr inbounds i8, i8* %output.addr.0.pn108, i32 2
  store i8 %cond58, i8* %output.addr.1109, align 1, !tbaa !12
  %8 = load i8, i8* %arrayidx43, align 1, !tbaa !12
  %9 = and i8 %8, 15
  %cmp68 = icmp ugt i8 %9, 9
  %sub73 = add nuw nsw i8 %9, 87
  %add76 = or i8 %9, 48
  %cond78 = select i1 %cmp68, i8 %sub73, i8 %add76
  store i8 %cond78, i8* %incdec.ptr60, align 1, !tbaa !12
  %output.addr.1 = getelementptr inbounds i8, i8* %output.addr.0.pn108, i32 3
  %dec39 = add i32 %dec39110, -1
  %tobool.not = icmp eq i32 %dec39, 0
  br i1 %tobool.not, label %while.end81, label %while.body40

while.end81:                                      ; preds = %while.body40, %if.end
  %output.addr.1.lcssa = phi i8* [ %output.addr.1104, %if.end ], [ %output.addr.1, %while.body40 ]
  ret i8* %output.addr.1.lcssa
}

; Function Attrs: nofree norecurse nounwind
define hidden nonnull i8* @uint2bin(i8* %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %0 = icmp ne i32 %length, 0
  %umin = zext i1 %0 to i32
  br label %while.cond

while.cond:                                       ; preds = %land.rhs, %entry
  %length.addr.0 = phi i32 [ %length, %entry ], [ %sub, %land.rhs ]
  %cmp = icmp ugt i32 %length.addr.0, 1
  br i1 %cmp, label %land.rhs, label %while.cond.while.end_crit_edge

while.cond.while.end_crit_edge:                   ; preds = %while.cond
  %not. = xor i1 %0, true
  %.pre = sext i1 %not. to i32
  br label %while.end

land.rhs:                                         ; preds = %while.cond
  %sub = add i32 %length.addr.0, -1
  %arrayidx = getelementptr inbounds i8, i8* %input, i32 %sub
  %1 = load i8, i8* %arrayidx, align 1, !tbaa !12
  %cmp1 = icmp eq i8 %1, 0
  br i1 %cmp1, label %while.cond, label %while.end

while.end:                                        ; preds = %land.rhs, %while.cond.while.end_crit_edge
  %sub4.pre-phi = phi i32 [ %.pre, %while.cond.while.end_crit_edge ], [ %sub, %land.rhs ]
  %length.addr.0.lcssa = phi i32 [ %umin, %while.cond.while.end_crit_edge ], [ %length.addr.0, %land.rhs ]
  %incdec.ptr = getelementptr inbounds i8, i8* %output, i32 1
  store i8 48, i8* %output, align 1, !tbaa !12
  %incdec.ptr3 = getelementptr inbounds i8, i8* %output, i32 2
  store i8 98, i8* %incdec.ptr, align 1, !tbaa !12
  %arrayidx5 = getelementptr inbounds i8, i8* %input, i32 %sub4.pre-phi
  %2 = load i8, i8* %arrayidx5, align 1, !tbaa !12
  %tobool.not82 = icmp sgt i8 %2, -1
  br i1 %tobool.not82, label %while.body12, label %while.body20.preheader

while.cond17.preheader:                           ; preds = %while.body12
  %tobool19.not77 = icmp eq i32 %dec15, 0
  br i1 %tobool19.not77, label %while.cond30.preheader, label %while.body20.preheader

while.body20.preheader:                           ; preds = %while.end, %while.cond17.preheader
  %i.180.ph = phi i32 [ 8, %while.end ], [ %dec15, %while.cond17.preheader ]
  %v.179.ph = phi i8 [ %2, %while.end ], [ %shl, %while.cond17.preheader ]
  br label %while.body20

while.body12:                                     ; preds = %while.end, %while.body12
  %i.084 = phi i32 [ %dec15, %while.body12 ], [ 8, %while.end ]
  %v.083 = phi i8 [ %shl, %while.body12 ], [ %2, %while.end ]
  %shl = shl nuw i8 %v.083, 1
  %dec15 = add nsw i32 %i.084, -1
  %cmp7 = icmp ugt i32 %i.084, 1
  %tobool.not = icmp sgt i8 %shl, -1
  %3 = and i1 %tobool.not, %cmp7
  br i1 %3, label %while.body12, label %while.cond17.preheader

while.cond30.preheader:                           ; preds = %while.body20, %while.cond17.preheader
  %output.addr.0.lcssa = phi i8* [ %incdec.ptr3, %while.cond17.preheader ], [ %incdec.ptr25, %while.body20 ]
  %tobool32.not73 = icmp eq i32 %sub4.pre-phi, 0
  br i1 %tobool32.not73, label %while.end48, label %while.body33

while.body20:                                     ; preds = %while.body20.preheader, %while.body20
  %i.180 = phi i32 [ %dec18, %while.body20 ], [ %i.180.ph, %while.body20.preheader ]
  %v.179 = phi i8 [ %shl27, %while.body20 ], [ %v.179.ph, %while.body20.preheader ]
  %output.addr.078 = phi i8* [ %incdec.ptr25, %while.body20 ], [ %incdec.ptr3, %while.body20.preheader ]
  %dec18 = add nsw i32 %i.180, -1
  %tobool23.not = icmp sgt i8 %v.179, -1
  %conv24 = select i1 %tobool23.not, i8 48, i8 49
  %incdec.ptr25 = getelementptr inbounds i8, i8* %output.addr.078, i32 1
  store i8 %conv24, i8* %output.addr.078, align 1, !tbaa !12
  %shl27 = shl i8 %v.179, 1
  %tobool19.not = icmp eq i32 %dec18, 0
  br i1 %tobool19.not, label %while.cond30.preheader, label %while.body20

while.body33:                                     ; preds = %while.cond30.preheader, %while.body33
  %dec3176 = phi i32 [ %dec31, %while.body33 ], [ %sub4.pre-phi, %while.cond30.preheader ]
  %length.addr.175 = phi i32 [ %dec3176, %while.body33 ], [ %length.addr.0.lcssa, %while.cond30.preheader ]
  %output.addr.174 = phi i8* [ %incdec.ptr44.7, %while.body33 ], [ %output.addr.0.lcssa, %while.cond30.preheader ]
  %sub35 = add i32 %length.addr.175, -2
  %arrayidx36 = getelementptr inbounds i8, i8* %input, i32 %sub35
  %4 = load i8, i8* %arrayidx36, align 1, !tbaa !12
  %tobool41.not = icmp sgt i8 %4, -1
  %conv43 = select i1 %tobool41.not, i8 48, i8 49
  %incdec.ptr44 = getelementptr inbounds i8, i8* %output.addr.174, i32 1
  store i8 %conv43, i8* %output.addr.174, align 1, !tbaa !12
  %shl46.mask = and i8 %4, 64
  %tobool41.not.1 = icmp eq i8 %shl46.mask, 0
  %conv43.1 = select i1 %tobool41.not.1, i8 48, i8 49
  %incdec.ptr44.1 = getelementptr inbounds i8, i8* %output.addr.174, i32 2
  store i8 %conv43.1, i8* %incdec.ptr44, align 1, !tbaa !12
  %shl46.1.mask = and i8 %4, 32
  %tobool41.not.2 = icmp eq i8 %shl46.1.mask, 0
  %conv43.2 = select i1 %tobool41.not.2, i8 48, i8 49
  %incdec.ptr44.2 = getelementptr inbounds i8, i8* %output.addr.174, i32 3
  store i8 %conv43.2, i8* %incdec.ptr44.1, align 1, !tbaa !12
  %shl46.2.mask = and i8 %4, 16
  %tobool41.not.3 = icmp eq i8 %shl46.2.mask, 0
  %conv43.3 = select i1 %tobool41.not.3, i8 48, i8 49
  %incdec.ptr44.3 = getelementptr inbounds i8, i8* %output.addr.174, i32 4
  store i8 %conv43.3, i8* %incdec.ptr44.2, align 1, !tbaa !12
  %shl46.3.mask = and i8 %4, 8
  %tobool41.not.4 = icmp eq i8 %shl46.3.mask, 0
  %conv43.4 = select i1 %tobool41.not.4, i8 48, i8 49
  %incdec.ptr44.4 = getelementptr inbounds i8, i8* %output.addr.174, i32 5
  store i8 %conv43.4, i8* %incdec.ptr44.3, align 1, !tbaa !12
  %shl46.4.mask = and i8 %4, 4
  %tobool41.not.5 = icmp eq i8 %shl46.4.mask, 0
  %conv43.5 = select i1 %tobool41.not.5, i8 48, i8 49
  %incdec.ptr44.5 = getelementptr inbounds i8, i8* %output.addr.174, i32 6
  store i8 %conv43.5, i8* %incdec.ptr44.4, align 1, !tbaa !12
  %shl46.5.mask = and i8 %4, 2
  %tobool41.not.6 = icmp eq i8 %shl46.5.mask, 0
  %conv43.6 = select i1 %tobool41.not.6, i8 48, i8 49
  %incdec.ptr44.6 = getelementptr inbounds i8, i8* %output.addr.174, i32 7
  store i8 %conv43.6, i8* %incdec.ptr44.5, align 1, !tbaa !12
  %shl46.6.mask = and i8 %4, 1
  %5 = or i8 %shl46.6.mask, 48
  %incdec.ptr44.7 = getelementptr inbounds i8, i8* %output.addr.174, i32 8
  store i8 %5, i8* %incdec.ptr44.6, align 1, !tbaa !12
  %dec31 = add i32 %dec3176, -1
  %tobool32.not = icmp eq i32 %dec31, 0
  br i1 %tobool32.not, label %while.end48, label %while.body33

while.end48:                                      ; preds = %while.body33, %while.cond30.preheader
  %output.addr.1.lcssa = phi i8* [ %output.addr.0.lcssa, %while.cond30.preheader ], [ %incdec.ptr44.7, %while.body33 ]
  ret i8* %output.addr.1.lcssa
}

; Function Attrs: nounwind writeonly
define hidden i8* @uint2dec(i8* %output, i64 %val) local_unnamed_addr #14 {
entry:
  %buf = alloca [20 x i8], align 16
  %0 = getelementptr inbounds [20 x i8], [20 x i8]* %buf, i32 0, i32 0
  call void @llvm.lifetime.start.p0i8(i64 20, i8* nonnull %0) #19
  br label %do.body

do.body:                                          ; preds = %do.body, %entry
  %val.addr.0 = phi i64 [ %val, %entry ], [ %div, %do.body ]
  %len.0 = phi i32 [ 0, %entry ], [ %inc, %do.body ]
  %val.addr.0.frozen = freeze i64 %val.addr.0
  %div = udiv i64 %val.addr.0.frozen, 10
  %1 = mul i64 %div, 10
  %rem.decomposed = sub i64 %val.addr.0.frozen, %1
  %conv = trunc i64 %rem.decomposed to i8
  %inc = add nuw nsw i32 %len.0, 1
  %arrayidx = getelementptr inbounds [20 x i8], [20 x i8]* %buf, i32 0, i32 %len.0
  store i8 %conv, i8* %arrayidx, align 1, !tbaa !12
  %2 = icmp ult i64 %val.addr.0, 10
  br i1 %2, label %while.body.preheader, label %do.body

while.body.preheader:                             ; preds = %do.body
  %add14 = or i8 %conv, 48
  %incdec.ptr15 = getelementptr inbounds i8, i8* %output, i32 1
  store i8 %add14, i8* %output, align 1, !tbaa !12
  %tobool1.not17 = icmp eq i32 %len.0, 0
  br i1 %tobool1.not17, label %while.end, label %while.body.while.body_crit_edge

while.body.while.body_crit_edge:                  ; preds = %while.body.preheader, %while.body.while.body_crit_edge
  %dec19.in = phi i32 [ %dec19, %while.body.while.body_crit_edge ], [ %len.0, %while.body.preheader ]
  %incdec.ptr18 = phi i8* [ %incdec.ptr, %while.body.while.body_crit_edge ], [ %incdec.ptr15, %while.body.preheader ]
  %dec19 = add nsw i32 %dec19.in, -1
  %arrayidx2.phi.trans.insert = getelementptr inbounds [20 x i8], [20 x i8]* %buf, i32 0, i32 %dec19
  %.pre = load i8, i8* %arrayidx2.phi.trans.insert, align 1, !tbaa !12
  %add = add i8 %.pre, 48
  %incdec.ptr = getelementptr inbounds i8, i8* %incdec.ptr18, i32 1
  store i8 %add, i8* %incdec.ptr18, align 1, !tbaa !12
  %tobool1.not = icmp eq i32 %dec19, 0
  br i1 %tobool1.not, label %while.end, label %while.body.while.body_crit_edge

while.end:                                        ; preds = %while.body.while.body_crit_edge, %while.body.preheader
  %incdec.ptr.lcssa = phi i8* [ %incdec.ptr15, %while.body.preheader ], [ %incdec.ptr, %while.body.while.body_crit_edge ]
  call void @llvm.lifetime.end.p0i8(i64 20, i8* nonnull %0) #19
  ret i8* %incdec.ptr.lcssa
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #15

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #15

; Function Attrs: nounwind
define hidden i8* @uint128dec(i8* %output, i128 %val128) local_unnamed_addr #9 {
entry:
  %val128.addr = alloca i128, align 16
  %divisor = alloca i128, align 16
  %q = alloca i128, align 16
  %r = alloca i128, align 16
  %buf = alloca [40 x i8], align 16
  store i128 %val128, i128* %val128.addr, align 16, !tbaa !48
  %0 = bitcast i128* %divisor to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %0) #19
  store i128 10000000000000000000, i128* %divisor, align 16, !tbaa !48
  %1 = bitcast i128* %q to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %1) #19
  %2 = bitcast i128* %r to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %2) #19
  %3 = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 0
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %3) #19
  %call = call i32 @udivmod128(i128* nonnull %val128.addr, i128* nonnull %divisor, i128* nonnull %r, i128* nonnull %q) #17
  %4 = load i128, i128* %r, align 16, !tbaa !48
  %conv = trunc i128 %4 to i64
  br label %do.body

do.body:                                          ; preds = %do.body, %entry
  %len.0 = phi i32 [ 0, %entry ], [ %inc, %do.body ]
  %val.0 = phi i64 [ %conv, %entry ], [ %div, %do.body ]
  %val.0.frozen = freeze i64 %val.0
  %div = udiv i64 %val.0.frozen, 10
  %5 = mul i64 %div, 10
  %rem.decomposed = sub i64 %val.0.frozen, %5
  %conv1 = trunc i64 %rem.decomposed to i8
  %inc = add nuw nsw i32 %len.0, 1
  %arrayidx = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.0
  store i8 %conv1, i8* %arrayidx, align 1, !tbaa !12
  %6 = icmp ult i64 %val.0, 10
  br i1 %6, label %do.end, label %do.body

do.end:                                           ; preds = %do.body
  %call2 = call i32 @udivmod128(i128* nonnull %q, i128* nonnull %divisor, i128* nonnull %r, i128* nonnull %q) #17
  %7 = load i128, i128* %r, align 16, !tbaa !48
  %conv3 = trunc i128 %7 to i64
  %tobool4.not = icmp eq i64 %conv3, 0
  br i1 %tobool4.not, label %if.end, label %while.cond.preheader

while.cond.preheader:                             ; preds = %do.end
  %cmp73 = icmp ult i32 %len.0, 18
  br i1 %cmp73, label %while.body, label %do.body8.preheader

while.body:                                       ; preds = %while.cond.preheader, %while.body
  %len.174 = phi i32 [ %inc6, %while.body ], [ %inc, %while.cond.preheader ]
  %inc6 = add i32 %len.174, 1
  %arrayidx7 = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.174
  store i8 0, i8* %arrayidx7, align 1, !tbaa !12
  %exitcond76.not = icmp eq i32 %inc6, 19
  br i1 %exitcond76.not, label %do.body8.preheader, label %while.body

do.body8.preheader:                               ; preds = %while.body, %while.cond.preheader
  %len.2.ph = phi i32 [ %inc, %while.cond.preheader ], [ 19, %while.body ]
  br label %do.body8

do.body8:                                         ; preds = %do.body8.preheader, %do.body8
  %len.2 = phi i32 [ %inc11, %do.body8 ], [ %len.2.ph, %do.body8.preheader ]
  %val.1 = phi i64 [ %div13, %do.body8 ], [ %conv3, %do.body8.preheader ]
  %val.1.frozen = freeze i64 %val.1
  %div13 = udiv i64 %val.1.frozen, 10
  %8 = mul i64 %div13, 10
  %rem9.decomposed = sub i64 %val.1.frozen, %8
  %conv10 = trunc i64 %rem9.decomposed to i8
  %inc11 = add nuw nsw i32 %len.2, 1
  %arrayidx12 = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.2
  store i8 %conv10, i8* %arrayidx12, align 1, !tbaa !12
  %9 = icmp ult i64 %val.1, 10
  br i1 %9, label %if.end, label %do.body8

if.end:                                           ; preds = %do.body8, %do.end
  %len.3 = phi i32 [ %inc, %do.end ], [ %inc11, %do.body8 ]
  %10 = load i128, i128* %q, align 16, !tbaa !48
  %conv17 = trunc i128 %10 to i64
  %tobool18.not = icmp eq i64 %conv17, 0
  br i1 %tobool18.not, label %while.body39.preheader, label %while.cond20.preheader

while.cond20.preheader:                           ; preds = %if.end
  %cmp2170 = icmp slt i32 %len.3, 38
  br i1 %cmp2170, label %while.body23, label %do.body27.preheader

while.body23:                                     ; preds = %while.cond20.preheader, %while.body23
  %len.471 = phi i32 [ %inc24, %while.body23 ], [ %len.3, %while.cond20.preheader ]
  %inc24 = add i32 %len.471, 1
  %arrayidx25 = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.471
  store i8 0, i8* %arrayidx25, align 1, !tbaa !12
  %exitcond.not = icmp eq i32 %inc24, 38
  br i1 %exitcond.not, label %do.body27.preheader, label %while.body23

do.body27.preheader:                              ; preds = %while.body23, %while.cond20.preheader
  %len.5.ph = phi i32 [ %len.3, %while.cond20.preheader ], [ 38, %while.body23 ]
  br label %do.body27

do.body27:                                        ; preds = %do.body27.preheader, %do.body27
  %len.5 = phi i32 [ %inc30, %do.body27 ], [ %len.5.ph, %do.body27.preheader ]
  %val.2 = phi i64 [ %div32, %do.body27 ], [ %conv17, %do.body27.preheader ]
  %val.2.frozen = freeze i64 %val.2
  %div32 = udiv i64 %val.2.frozen, 10
  %11 = mul i64 %div32, 10
  %rem28.decomposed = sub i64 %val.2.frozen, %11
  %conv29 = trunc i64 %rem28.decomposed to i8
  %inc30 = add nsw i32 %len.5, 1
  %arrayidx31 = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.5
  store i8 %conv29, i8* %arrayidx31, align 1, !tbaa !12
  %12 = icmp ult i64 %val.2, 10
  br i1 %12, label %if.end36, label %do.body27

if.end36:                                         ; preds = %do.body27
  %tobool38.not67 = icmp eq i32 %inc30, 0
  br i1 %tobool38.not67, label %while.end43, label %while.body39.preheader

while.body39.preheader:                           ; preds = %if.end, %if.end36
  %dec69.in.ph = phi i32 [ %len.3, %if.end ], [ %inc30, %if.end36 ]
  br label %while.body39

while.body39:                                     ; preds = %while.body39.preheader, %while.body39
  %dec69.in = phi i32 [ %dec69, %while.body39 ], [ %dec69.in.ph, %while.body39.preheader ]
  %output.addr.068 = phi i8* [ %incdec.ptr, %while.body39 ], [ %output, %while.body39.preheader ]
  %dec69 = add nsw i32 %dec69.in, -1
  %arrayidx40 = getelementptr inbounds [40 x i8], [40 x i8]* %buf, i32 0, i32 %dec69
  %13 = load i8, i8* %arrayidx40, align 1, !tbaa !12
  %add = add i8 %13, 48
  %incdec.ptr = getelementptr inbounds i8, i8* %output.addr.068, i32 1
  store i8 %add, i8* %output.addr.068, align 1, !tbaa !12
  %tobool38.not = icmp eq i32 %dec69, 0
  br i1 %tobool38.not, label %while.end43, label %while.body39

while.end43:                                      ; preds = %while.body39, %if.end36
  %output.addr.0.lcssa = phi i8* [ %output, %if.end36 ], [ %incdec.ptr, %while.body39 ]
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %3) #19
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %2) #19
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %1) #19
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %0) #19
  ret i8* %output.addr.0.lcssa
}

; Function Attrs: nounwind
define hidden i8* @uint256dec(i8* %output, i256* nocapture readonly %val256) local_unnamed_addr #9 {
do.body.preheader:
  %divisor = alloca i256, align 8
  %q = alloca i256, align 8
  %r = alloca i256, align 8
  %buf = alloca [80 x i8], align 16
  %0 = bitcast i256* %divisor to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %0) #19
  store i256 10000000000000000000, i256* %divisor, align 8, !tbaa !50
  %1 = bitcast i256* %q to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %1) #19
  %2 = load i256, i256* %val256, align 8, !tbaa !50
  store i256 %2, i256* %q, align 8, !tbaa !50
  %3 = bitcast i256* %r to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %3) #19
  %4 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 0
  call void @llvm.lifetime.start.p0i8(i64 80, i8* nonnull %4) #19
  %call = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #17
  %5 = load i256, i256* %r, align 8, !tbaa !50
  %conv = trunc i256 %5 to i64
  br label %do.body

for.cond:                                         ; preds = %do.end
  %call.1 = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #17
  %6 = load i256, i256* %r, align 8, !tbaa !50
  %conv.1 = trunc i256 %6 to i64
  %cmp162.1 = icmp ult i32 %len.2, 18
  br i1 %cmp162.1, label %while.body.1, label %do.body.1.preheader

do.body:                                          ; preds = %do.body.preheader, %do.body
  %len.2 = phi i32 [ %inc4, %do.body ], [ 0, %do.body.preheader ]
  %val.0 = phi i64 [ %div, %do.body ], [ %conv, %do.body.preheader ]
  %val.0.frozen = freeze i64 %val.0
  %div = udiv i64 %val.0.frozen, 10
  %7 = mul i64 %div, 10
  %rem.decomposed = sub i64 %val.0.frozen, %7
  %conv3 = trunc i64 %rem.decomposed to i8
  %inc4 = add nuw nsw i32 %len.2, 1
  %arrayidx5 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2
  store i8 %conv3, i8* %arrayidx5, align 1, !tbaa !12
  %8 = icmp ult i64 %val.0, 10
  br i1 %8, label %do.end, label %do.body

do.end:                                           ; preds = %do.body
  %9 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not = icmp eq i256 %9, 0
  br i1 %cmp6.not, label %while.body25.preheader, label %for.cond

cleanup8:                                         ; preds = %do.end.3
  %extract.t = trunc i256 %23 to i64
  %tobool11.not = icmp eq i64 %extract.t, 0
  br i1 %tobool11.not, label %if.end22, label %do.body13

do.body13:                                        ; preds = %cleanup8, %do.body13
  %len.4 = phi i32 [ %inc16, %do.body13 ], [ %inc4.3, %cleanup8 ]
  %val9.0 = phi i64 [ %div18, %do.body13 ], [ %extract.t, %cleanup8 ]
  %val9.0.frozen = freeze i64 %val9.0
  %div18 = udiv i64 %val9.0.frozen, 10
  %10 = mul i64 %div18, 10
  %rem14.decomposed = sub i64 %val9.0.frozen, %10
  %conv15 = trunc i64 %rem14.decomposed to i8
  %inc16 = add nsw i32 %len.4, 1
  %arrayidx17 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.4
  store i8 %conv15, i8* %arrayidx17, align 1, !tbaa !12
  %11 = icmp ult i64 %val9.0, 10
  br i1 %11, label %if.end22, label %do.body13

if.end22:                                         ; preds = %do.body13, %do.end.3, %do.end.2, %do.end.1, %cleanup8
  %len.5 = phi i32 [ %inc4.3, %cleanup8 ], [ %inc4.3, %do.end.3 ], [ %inc4.2, %do.end.2 ], [ %inc4.1, %do.end.1 ], [ %inc16, %do.body13 ]
  %tobool24.not59 = icmp eq i32 %len.5, 0
  br i1 %tobool24.not59, label %while.end30, label %while.body25.preheader

while.body25.preheader:                           ; preds = %do.end, %if.end22
  %dec61.in.ph = phi i32 [ %inc4, %do.end ], [ %len.5, %if.end22 ]
  br label %while.body25

while.body25:                                     ; preds = %while.body25.preheader, %while.body25
  %dec61.in = phi i32 [ %dec61, %while.body25 ], [ %dec61.in.ph, %while.body25.preheader ]
  %output.addr.060 = phi i8* [ %incdec.ptr, %while.body25 ], [ %output, %while.body25.preheader ]
  %dec61 = add nsw i32 %dec61.in, -1
  %arrayidx26 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %dec61
  %12 = load i8, i8* %arrayidx26, align 1, !tbaa !12
  %add28 = add i8 %12, 48
  %incdec.ptr = getelementptr inbounds i8, i8* %output.addr.060, i32 1
  store i8 %add28, i8* %output.addr.060, align 1, !tbaa !12
  %tobool24.not = icmp eq i32 %dec61, 0
  br i1 %tobool24.not, label %while.end30, label %while.body25

while.end30:                                      ; preds = %while.body25, %if.end22
  %output.addr.0.lcssa = phi i8* [ %output, %if.end22 ], [ %incdec.ptr, %while.body25 ]
  call void @llvm.lifetime.end.p0i8(i64 80, i8* nonnull %4) #19
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %3) #19
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %1) #19
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %0) #19
  ret i8* %output.addr.0.lcssa

while.body.1:                                     ; preds = %for.cond, %while.body.1
  %len.163.1 = phi i32 [ %inc.1, %while.body.1 ], [ %inc4, %for.cond ]
  %inc.1 = add nuw nsw i32 %len.163.1, 1
  %arrayidx.1 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.163.1
  store i8 0, i8* %arrayidx.1, align 1, !tbaa !12
  %exitcond.1.not = icmp eq i32 %inc.1, 19
  br i1 %exitcond.1.not, label %do.body.1.preheader, label %while.body.1

do.body.1.preheader:                              ; preds = %while.body.1, %for.cond
  %len.2.1.ph = phi i32 [ %inc4, %for.cond ], [ 19, %while.body.1 ]
  br label %do.body.1

do.body.1:                                        ; preds = %do.body.1.preheader, %do.body.1
  %len.2.1 = phi i32 [ %inc4.1, %do.body.1 ], [ %len.2.1.ph, %do.body.1.preheader ]
  %val.0.1 = phi i64 [ %div.1, %do.body.1 ], [ %conv.1, %do.body.1.preheader ]
  %val.0.1.frozen = freeze i64 %val.0.1
  %div.1 = udiv i64 %val.0.1.frozen, 10
  %13 = mul i64 %div.1, 10
  %rem.1.decomposed = sub i64 %val.0.1.frozen, %13
  %conv3.1 = trunc i64 %rem.1.decomposed to i8
  %inc4.1 = add nsw i32 %len.2.1, 1
  %arrayidx5.1 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2.1
  store i8 %conv3.1, i8* %arrayidx5.1, align 1, !tbaa !12
  %14 = icmp ult i64 %val.0.1, 10
  br i1 %14, label %do.end.1, label %do.body.1

do.end.1:                                         ; preds = %do.body.1
  %15 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not.1 = icmp eq i256 %15, 0
  br i1 %cmp6.not.1, label %if.end22, label %for.cond.1

for.cond.1:                                       ; preds = %do.end.1
  %call.2 = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #17
  %16 = load i256, i256* %r, align 8, !tbaa !50
  %conv.2 = trunc i256 %16 to i64
  %cmp162.2 = icmp slt i32 %len.2.1, 37
  br i1 %cmp162.2, label %while.body.2, label %do.body.2.preheader

while.body.2:                                     ; preds = %for.cond.1, %while.body.2
  %len.163.2 = phi i32 [ %inc.2, %while.body.2 ], [ %inc4.1, %for.cond.1 ]
  %inc.2 = add nsw i32 %len.163.2, 1
  %arrayidx.2 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.163.2
  store i8 0, i8* %arrayidx.2, align 1, !tbaa !12
  %exitcond.2.not = icmp eq i32 %inc.2, 38
  br i1 %exitcond.2.not, label %do.body.2.preheader, label %while.body.2

do.body.2.preheader:                              ; preds = %while.body.2, %for.cond.1
  %len.2.2.ph = phi i32 [ %inc4.1, %for.cond.1 ], [ 38, %while.body.2 ]
  br label %do.body.2

do.body.2:                                        ; preds = %do.body.2.preheader, %do.body.2
  %len.2.2 = phi i32 [ %inc4.2, %do.body.2 ], [ %len.2.2.ph, %do.body.2.preheader ]
  %val.0.2 = phi i64 [ %div.2, %do.body.2 ], [ %conv.2, %do.body.2.preheader ]
  %val.0.2.frozen = freeze i64 %val.0.2
  %div.2 = udiv i64 %val.0.2.frozen, 10
  %17 = mul i64 %div.2, 10
  %rem.2.decomposed = sub i64 %val.0.2.frozen, %17
  %conv3.2 = trunc i64 %rem.2.decomposed to i8
  %inc4.2 = add nsw i32 %len.2.2, 1
  %arrayidx5.2 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2.2
  store i8 %conv3.2, i8* %arrayidx5.2, align 1, !tbaa !12
  %18 = icmp ult i64 %val.0.2, 10
  br i1 %18, label %do.end.2, label %do.body.2

do.end.2:                                         ; preds = %do.body.2
  %19 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not.2 = icmp eq i256 %19, 0
  br i1 %cmp6.not.2, label %if.end22, label %for.cond.2

for.cond.2:                                       ; preds = %do.end.2
  %call.3 = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #17
  %20 = load i256, i256* %r, align 8, !tbaa !50
  %conv.3 = trunc i256 %20 to i64
  %cmp162.3 = icmp slt i32 %len.2.2, 56
  br i1 %cmp162.3, label %while.body.3, label %do.body.3.preheader

while.body.3:                                     ; preds = %for.cond.2, %while.body.3
  %len.163.3 = phi i32 [ %inc.3, %while.body.3 ], [ %inc4.2, %for.cond.2 ]
  %inc.3 = add nsw i32 %len.163.3, 1
  %arrayidx.3 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.163.3
  store i8 0, i8* %arrayidx.3, align 1, !tbaa !12
  %exitcond.3.not = icmp eq i32 %inc.3, 57
  br i1 %exitcond.3.not, label %do.body.3.preheader, label %while.body.3

do.body.3.preheader:                              ; preds = %while.body.3, %for.cond.2
  %len.2.3.ph = phi i32 [ %inc4.2, %for.cond.2 ], [ 57, %while.body.3 ]
  br label %do.body.3

do.body.3:                                        ; preds = %do.body.3.preheader, %do.body.3
  %len.2.3 = phi i32 [ %inc4.3, %do.body.3 ], [ %len.2.3.ph, %do.body.3.preheader ]
  %val.0.3 = phi i64 [ %div.3, %do.body.3 ], [ %conv.3, %do.body.3.preheader ]
  %val.0.3.frozen = freeze i64 %val.0.3
  %div.3 = udiv i64 %val.0.3.frozen, 10
  %21 = mul i64 %div.3, 10
  %rem.3.decomposed = sub i64 %val.0.3.frozen, %21
  %conv3.3 = trunc i64 %rem.3.decomposed to i8
  %inc4.3 = add nsw i32 %len.2.3, 1
  %arrayidx5.3 = getelementptr inbounds [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2.3
  store i8 %conv3.3, i8* %arrayidx5.3, align 1, !tbaa !12
  %22 = icmp ult i64 %val.0.3, 10
  br i1 %22, label %do.end.3, label %do.body.3

do.end.3:                                         ; preds = %do.body.3
  %23 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not.3 = icmp eq i256 %23, 0
  br i1 %cmp6.not.3, label %if.end22, label %cleanup8
}

declare void @storageStore(i8*, i8*)

declare void @storageLoad(i8*, i8*)

declare i32 @getCallDataSize()

declare i32 @getCodeSize()

declare i32 @getReturnDataSize()

declare void @callDataCopy(i8*, i32, i32)

declare void @codeCopy(i8*, i32, i32)

declare void @returnDataCopy(i8*, i32, i32)

declare void @printMem(i8*, i32)

declare i32 @create(i8*, i8*, i32, i8*)

declare i32 @call(i64, i8*, i8*, i8*, i32)

declare i32 @callStatic(i64, i8*, i8*, i32)

declare i32 @callDelegate(i64, i8*, i8*, i32)

declare void @getCallValue(i8*)

declare void @getAddress(i8*)

declare void @getCaller(i8*)

declare void @getExternalBalance(i8*, i8*)

declare i32 @getBlockHash(i64, i8*)

declare void @getBlockCoinbase(i8*)

declare void @getBlockDifficulty(i8*)

declare i64 @getGasLeft()

declare i64 @getBlockGasLimit()

declare i64 @getBlockTimestamp()

declare i64 @getBlockNumber()

declare void @getTxGasPrice(i8*)

declare void @getTxOrigin(i8*)

declare void @log(i8*, i32, i32, i8*, i8*, i8*, i8*)

; Function Attrs: noreturn
declare void @finish(i8*, i32) #16

; Function Attrs: noreturn
declare void @revert(i8*, i32) #16

; Function Attrs: noreturn
declare void @selfDestruct(i8*) #16

define internal i32 @"PuppetPool::ReentrancyGuard::function::v_get__status"(i256* %0) {
entry:
  %slot = alloca i256, align 8
  store i256 0, i256* %slot, align 8
  %buf = alloca i8, i32 32, align 1
  %1 = bitcast i256* %slot to i8*
  call void @storageLoad(i8* %1, i8* %buf)
  %2 = bitcast i8* %buf to i256*
  %loaded_int = load i256, i256* %2, align 8
  store i256 %loaded_int, i256* %0, align 8
  ret i32 0
}

define internal i32 @"PuppetPool::ReentrancyGuard::function::v_set__status__uint256"(i256 %0) {
entry:
  %1 = alloca i256, align 8
  %slot = alloca i256, align 8
  store i256 0, i256* %slot, align 8
  store i256 %0, i256* %1, align 8
  %2 = bitcast i256* %slot to i8*
  %3 = bitcast i256* %1 to i8*
  call void @storageStore(i8* %2, i8* %3)
  ret i32 0
}

define internal i32 @"PuppetPool::ReentrancyGuard::function::v_neq__uint256_uint256"(i256 %0, i256 %1, i1* %2) {
entry:
  %3 = icmp eq i256 %0, %1
  %4 = icmp eq i1 %3, false
  store i1 %4, i1* %2, align 1
  ret i32 0
}

define internal i32 @"PuppetPool::ReentrancyGuard::function::v_require__bool_string"(i1 %0, %struct.vector* %1) {
entry:
  %uint328 = alloca i32, align 4
  %uint322 = alloca i32, align 4
  %uint32 = alloca i32, align 4
  br i1 %0, label %noassert, label %doassert

noassert:                                         ; preds = %entry
  ret i32 0

doassert:                                         ; preds = %entry
  %vector_len = getelementptr %struct.vector, %struct.vector* %1, i32 0, i32 0
  %vector_is_null = icmp eq %struct.vector* %1, null
  %vector_len1 = load i32, i32* %vector_len, align 4
  %length = select i1 %vector_is_null, i32 0, i32 %vector_len1
  %2 = add i32 %length, 63
  %3 = and i32 %2, -32
  %4 = add i32 36, %3
  %5 = call i8* @__malloc(i32 %4)
  store i32 147028384, i32* %uint32, align 4
  %store = bitcast i32* %uint32 to i8*
  call void @__leNtobeN(i8* %store, i8* %5, i32 4)
  %6 = getelementptr i8, i8* %5, i32 4
  %7 = udiv i32 %4, 8
  call void @__bzero8(i8* %6, i32 %7)
  %8 = getelementptr i8, i8* %6, i32 32
  store i32 32, i32* %uint322, align 4
  %store3 = bitcast i32* %uint322 to i8*
  call void @__leNtobe32(i8* %store3, i8* %6, i32 4)
  %9 = getelementptr i8, i8* %6, i32 32
  %vector_len4 = getelementptr %struct.vector, %struct.vector* %1, i32 0, i32 0
  %vector_is_null5 = icmp eq %struct.vector* %1, null
  %vector_len6 = load i32, i32* %vector_len4, align 4
  %length7 = select i1 %vector_is_null5, i32 0, i32 %vector_len6
  store i32 %length7, i32* %uint328, align 4
  %store9 = bitcast i32* %uint328 to i8*
  call void @__leNtobe32(i8* %store9, i8* %8, i32 4)
  %10 = getelementptr i8, i8* %8, i32 32
  %data = getelementptr %struct.vector, %struct.vector* %1, i32 0, i32 2
  %data10 = bitcast [0 x i8]* %data to i8*
  call void @__memcpy(i8* %10, i8* %data10, i32 %length7)
  %11 = add i32 %length7, 31
  %12 = and i32 %11, -32
  %13 = getelementptr i8, i8* %10, i32 %12
  %14 = add i32 64, %12
  call void @revert(i8* %5, i32 %4)
  unreachable
}

define internal i32 @"PuppetPool::ReentrancyGuard::constructor::861731d5"() {
entry:
  %0 = call i32 @"PuppetPool::ReentrancyGuard::function::v_set__status__uint256"(i256 1)
  %success = icmp eq i32 %0, 0
  br i1 %success, label %success1, label %bail

success1:                                         ; preds = %entry
  ret i32 0

bail:                                             ; preds = %entry
  ret i32 %0
}

define internal i32 @"PuppetPool::Address::function::sendValue__address_uint256"([20 x i8] %0, i256 %1) {
entry:
  %uint3233 = alloca i32, align 4
  %uint3227 = alloca i32, align 4
  %uint3225 = alloca i32, align 4
  %uint3210 = alloca i32, align 4
  %uint324 = alloca i32, align 4
  %uint32 = alloca i32, align 4
  %self_address = alloca [20 x i8], align 1
  %2 = bitcast [20 x i8]* %self_address to i8*
  call void @getAddress(i8* %2)
  %self_address1 = load [20 x i8], [20 x i8]* %self_address, align 1
  %address = alloca [20 x i8], align 1
  store [20 x i8] %self_address1, [20 x i8]* %address, align 1
  %balance = alloca i128, align 8
  %3 = bitcast [20 x i8]* %address to i8*
  %4 = bitcast i128* %balance to i8*
  call void @getExternalBalance(i8* %3, i8* %4)
  %balance2 = load i128, i128* %balance, align 8
  %5 = sext i128 %balance2 to i256
  %6 = icmp uge i256 %5, %1
  br i1 %6, label %noassert, label %doassert

noassert:                                         ; preds = %entry
  %7 = icmp uge i256 %1, 340282366920938463463374607431768211456
  br i1 %7, label %out_of_bounds, label %in_bounds

doassert:                                         ; preds = %entry
  %8 = call %struct.vector.0* @vector_new(i32 29, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([29 x i8], [29 x i8]* @const_string, i32 0, i32 0))
  %vector = bitcast %struct.vector.0* %8 to %struct.vector*
  %vector_len = getelementptr %struct.vector, %struct.vector* %vector, i32 0, i32 0
  %vector_is_null = icmp eq %struct.vector* %vector, null
  %vector_len3 = load i32, i32* %vector_len, align 4
  %length = select i1 %vector_is_null, i32 0, i32 %vector_len3
  %9 = add i32 %length, 63
  %10 = and i32 %9, -32
  %11 = add i32 36, %10
  %12 = call i8* @__malloc(i32 %11)
  store i32 147028384, i32* %uint32, align 4
  %store = bitcast i32* %uint32 to i8*
  call void @__leNtobeN(i8* %store, i8* %12, i32 4)
  %13 = getelementptr i8, i8* %12, i32 4
  %14 = udiv i32 %11, 8
  call void @__bzero8(i8* %13, i32 %14)
  %15 = getelementptr i8, i8* %13, i32 32
  store i32 32, i32* %uint324, align 4
  %store5 = bitcast i32* %uint324 to i8*
  call void @__leNtobe32(i8* %store5, i8* %13, i32 4)
  %16 = getelementptr i8, i8* %13, i32 32
  %vector_len6 = getelementptr %struct.vector, %struct.vector* %vector, i32 0, i32 0
  %vector_is_null7 = icmp eq %struct.vector* %vector, null
  %vector_len8 = load i32, i32* %vector_len6, align 4
  %length9 = select i1 %vector_is_null7, i32 0, i32 %vector_len8
  store i32 %length9, i32* %uint3210, align 4
  %store11 = bitcast i32* %uint3210 to i8*
  call void @__leNtobe32(i8* %store11, i8* %15, i32 4)
  %17 = getelementptr i8, i8* %15, i32 32
  %data = getelementptr %struct.vector, %struct.vector* %vector, i32 0, i32 2
  %data12 = bitcast [0 x i8]* %data to i8*
  call void @__memcpy(i8* %17, i8* %data12, i32 %length9)
  %18 = add i32 %length9, 31
  %19 = and i32 %18, -32
  %20 = getelementptr i8, i8* %17, i32 %19
  %21 = add i32 64, %19
  call void @revert(i8* %12, i32 %11)
  unreachable

out_of_bounds:                                    ; preds = %noassert
  call void @revert(i8* null, i32 0)
  unreachable

in_bounds:                                        ; preds = %noassert
  %22 = trunc i256 %1 to i128
  %address13 = alloca i8, i32 20, align 1
  %address14 = bitcast i8* %address13 to [20 x i8]*
  store [20 x i8] %0, [20 x i8]* %address14, align 1
  %vector_len15 = load i32, i32* null, align 4
  %length16 = select i1 true, i32 0, i32 %vector_len15
  %balance17 = alloca i128, align 8
  store i128 %22, i128* %balance17, align 8
  %value_transfer = bitcast i128* %balance17 to i8*
  %23 = call i32 @call(i64 9223372036854775807, i8* %address13, i8* %value_transfer, i8* getelementptr (%struct.vector, %struct.vector* null, i32 0, i32 2, i32 0), i32 %length16)
  %success = icmp eq i32 %23, 0
  br i1 %success, label %noassert18, label %doassert19

noassert18:                                       ; preds = %in_bounds
  ret i32 0

doassert19:                                       ; preds = %in_bounds
  %24 = call %struct.vector.0* @vector_new(i32 58, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([58 x i8], [58 x i8]* @const_string.1, i32 0, i32 0))
  %vector20 = bitcast %struct.vector.0* %24 to %struct.vector*
  %vector_len21 = getelementptr %struct.vector, %struct.vector* %vector20, i32 0, i32 0
  %vector_is_null22 = icmp eq %struct.vector* %vector20, null
  %vector_len23 = load i32, i32* %vector_len21, align 4
  %length24 = select i1 %vector_is_null22, i32 0, i32 %vector_len23
  %25 = add i32 %length24, 63
  %26 = and i32 %25, -32
  %27 = add i32 36, %26
  %28 = call i8* @__malloc(i32 %27)
  store i32 147028384, i32* %uint3225, align 4
  %store26 = bitcast i32* %uint3225 to i8*
  call void @__leNtobeN(i8* %store26, i8* %28, i32 4)
  %29 = getelementptr i8, i8* %28, i32 4
  %30 = udiv i32 %27, 8
  call void @__bzero8(i8* %29, i32 %30)
  %31 = getelementptr i8, i8* %29, i32 32
  store i32 32, i32* %uint3227, align 4
  %store28 = bitcast i32* %uint3227 to i8*
  call void @__leNtobe32(i8* %store28, i8* %29, i32 4)
  %32 = getelementptr i8, i8* %29, i32 32
  %vector_len29 = getelementptr %struct.vector, %struct.vector* %vector20, i32 0, i32 0
  %vector_is_null30 = icmp eq %struct.vector* %vector20, null
  %vector_len31 = load i32, i32* %vector_len29, align 4
  %length32 = select i1 %vector_is_null30, i32 0, i32 %vector_len31
  store i32 %length32, i32* %uint3233, align 4
  %store34 = bitcast i32* %uint3233 to i8*
  call void @__leNtobe32(i8* %store34, i8* %31, i32 4)
  %33 = getelementptr i8, i8* %31, i32 32
  %data35 = getelementptr %struct.vector, %struct.vector* %vector20, i32 0, i32 2
  %data36 = bitcast [0 x i8]* %data35 to i8*
  call void @__memcpy(i8* %33, i8* %data36, i32 %length32)
  %34 = add i32 %length32, 31
  %35 = and i32 %34, -32
  %36 = getelementptr i8, i8* %33, i32 %35
  %37 = add i32 64, %35
  call void @revert(i8* %28, i32 %27)
  unreachable
}

define internal i32 @"PuppetPool::PuppetPool::function::deposits__address"([20 x i8] %0, i256* %1) {
entry:
  %keccak_src = alloca i8, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)), align 1
  %elem = getelementptr i8, i8* %keccak_src, i32 0
  %2 = bitcast i8* %elem to i256*
  store i256 1, i256* %2, align 8
  %elem1 = getelementptr i8, i8* %keccak_src, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32)
  %3 = bitcast i8* %elem1 to [20 x i8]*
  store [20 x i8] %0, [20 x i8]* %3, align 1
  %keccak_dst = alloca i256, align 8
  %balance = alloca i128, align 8
  store i128 0, i128* %balance, align 8
  %balance2 = bitcast i128* %balance to i8*
  %4 = call i32 @call(i64 9223372036854775807, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @keccak256_precompile, i32 0, i32 0), i8* %balance2, i8* %keccak_src, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)))
  %dest = bitcast i256* %keccak_dst to i8*
  call void @returnDataCopy(i8* %dest, i32 0, i32 32)
  %keccak256_hash = load i256, i256* %keccak_dst, align 8
  %slot = alloca i256, align 8
  store i256 %keccak256_hash, i256* %slot, align 8
  %buf = alloca i8, i32 32, align 1
  %5 = bitcast i256* %slot to i8*
  call void @storageLoad(i8* %5, i8* %buf)
  %6 = bitcast i8* %buf to i256*
  %loaded_int = load i256, i256* %6, align 8
  %int = add i256 %keccak256_hash, 1
  store i256 %loaded_int, i256* %1, align 8
  ret i32 0
}

define internal i32 @"PuppetPool::PuppetPool::function::uniswapPair"([20 x i8]* %0) {
entry:
  %slot = alloca i256, align 8
  store i256 2, i256* %slot, align 8
  %buf = alloca i8, i32 32, align 1
  %1 = bitcast i256* %slot to i8*
  call void @storageLoad(i8* %1, i8* %buf)
  %2 = bitcast i8* %buf to [20 x i8]*
  %loaded_address = load [20 x i8], [20 x i8]* %2, align 1
  store [20 x i8] %loaded_address, [20 x i8]* %0, align 1
  ret i32 0
}

define internal i32 @"PuppetPool::PuppetPool::function::token"([20 x i8]* %0) {
entry:
  %slot = alloca i256, align 8
  store i256 3, i256* %slot, align 8
  %buf = alloca i8, i32 32, align 1
  %1 = bitcast i256* %slot to i8*
  call void @storageLoad(i8* %1, i8* %buf)
  %2 = bitcast i8* %buf to [20 x i8]*
  %loaded_address = load [20 x i8], [20 x i8]* %2, align 1
  store [20 x i8] %loaded_address, [20 x i8]* %0, align 1
  ret i32 0
}

define internal i32 @"PuppetPool::PuppetPool::constructor::1c26cc85"([20 x i8] %0, [20 x i8] %1) {
entry:
  %2 = call i32 @"PuppetPool::ReentrancyGuard::constructor::861731d5"()
  %success = icmp eq i32 %2, 0
  br i1 %success, label %success1, label %bail

success1:                                         ; preds = %entry
  %slot = alloca i256, align 8
  %address = alloca [20 x i8], align 1
  store [20 x i8] %0, [20 x i8]* %address, align 1
  store i256 3, i256* %slot, align 8
  %value = alloca i256, align 8
  %value8 = bitcast i256* %value to i8*
  call void @__bzero8(i8* %value8, i32 4)
  %value2 = load [20 x i8], [20 x i8]* %address, align 1
  %3 = bitcast i256* %value to [20 x i8]*
  store [20 x i8] %value2, [20 x i8]* %3, align 1
  %4 = bitcast i256* %slot to i8*
  call void @storageStore(i8* %4, i8* %value8)
  %slot3 = alloca i256, align 8
  %address4 = alloca [20 x i8], align 1
  store [20 x i8] %1, [20 x i8]* %address4, align 1
  store i256 2, i256* %slot3, align 8
  %value5 = alloca i256, align 8
  %value86 = bitcast i256* %value5 to i8*
  call void @__bzero8(i8* %value86, i32 4)
  %value7 = load [20 x i8], [20 x i8]* %address4, align 1
  %5 = bitcast i256* %value5 to [20 x i8]*
  store [20 x i8] %value7, [20 x i8]* %5, align 1
  %6 = bitcast i256* %slot3 to i8*
  call void @storageStore(i8* %6, i8* %value86)
  ret i32 0

bail:                                             ; preds = %entry
  ret i32 %2
}

define internal i32 @"PuppetPool::PuppetPool::borrow__uint256::modifier0::nonReentrant"(i256 %0) {
entry:
  %1 = alloca i256, align 8
  %2 = call i32 @"PuppetPool::ReentrancyGuard::function::v_get__status"(i256* %1)
  %success = icmp eq i32 %2, 0
  br i1 %success, label %success1, label %bail

success1:                                         ; preds = %entry
  %3 = load i256, i256* %1, align 8
  %4 = alloca i1, align 1
  %5 = call i32 @"PuppetPool::ReentrancyGuard::function::v_neq__uint256_uint256"(i256 %3, i256 2, i1* %4)
  %success2 = icmp eq i32 %5, 0
  br i1 %success2, label %success3, label %bail4

bail:                                             ; preds = %entry
  ret i32 %2

success3:                                         ; preds = %success1
  %6 = load i1, i1* %4, align 1
  %7 = call %struct.vector.0* @vector_new(i32 31, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @const_string.2, i32 0, i32 0))
  %vector = bitcast %struct.vector.0* %7 to %struct.vector*
  %8 = call i32 @"PuppetPool::ReentrancyGuard::function::v_require__bool_string"(i1 %6, %struct.vector* %vector)
  %success5 = icmp eq i32 %8, 0
  br i1 %success5, label %success6, label %bail7

bail4:                                            ; preds = %success1
  ret i32 %5

success6:                                         ; preds = %success3
  %9 = call i32 @"PuppetPool::ReentrancyGuard::function::v_set__status__uint256"(i256 2)
  %success8 = icmp eq i32 %9, 0
  br i1 %success8, label %success9, label %bail10

bail7:                                            ; preds = %success3
  ret i32 %8

success9:                                         ; preds = %success6
  %10 = call i32 @"PuppetPool::PuppetPool::function::borrow__uint256"(i256 %0)
  %success11 = icmp eq i32 %10, 0
  br i1 %success11, label %success12, label %bail13

bail10:                                           ; preds = %success6
  ret i32 %9

success12:                                        ; preds = %success9
  %11 = call i32 @"PuppetPool::ReentrancyGuard::function::v_set__status__uint256"(i256 1)
  %success14 = icmp eq i32 %11, 0
  br i1 %success14, label %success15, label %bail16

bail13:                                           ; preds = %success9
  ret i32 %10

success15:                                        ; preds = %success12
  ret i32 0

bail16:                                           ; preds = %success12
  ret i32 %11
}

define internal i32 @"PuppetPool::PuppetPool::function::calculateDepositRequired__uint256"(i256 %0, i256* %1) {
entry:
  %quotient = alloca i256, align 8
  %remainder = alloca i256, align 8
  %divisor = alloca i256, align 8
  %dividend = alloca i256, align 8
  %2 = alloca i256, align 8
  %3 = alloca i256, align 8
  %4 = alloca i256, align 8
  %5 = alloca i256, align 8
  %6 = call i32 @"PuppetPool::PuppetPool::function::_computeOraclePrice"(i256* %5)
  %success = icmp eq i32 %6, 0
  br i1 %success, label %success1, label %bail

success1:                                         ; preds = %entry
  %7 = load i256, i256* %5, align 8
  store i256 %0, i256* %4, align 8
  store i256 %7, i256* %3, align 8
  %left = bitcast i256* %4 to i32*
  %right = bitcast i256* %3 to i32*
  %output = bitcast i256* %2 to i32*
  call void @__mul32(i32* %left, i32* %right, i32* %output, i32 8)
  %mul = load i256, i256* %2, align 8
  %8 = shl i256 %mul, 1
  store i256 %8, i256* %dividend, align 8
  store i256 1000000000000000000, i256* %divisor, align 8
  %udiv = call i32 @udivmod256(i256* %dividend, i256* %divisor, i256* %remainder, i256* %quotient)
  %success2 = icmp eq i32 %udiv, 0
  br i1 %success2, label %success3, label %bail4

bail:                                             ; preds = %entry
  ret i32 %6

success3:                                         ; preds = %success1
  %quotient5 = load i256, i256* %quotient, align 8
  store i256 %quotient5, i256* %1, align 8
  ret i32 0

bail4:                                            ; preds = %success1
  call void @revert(i8* null, i32 0)
  unreachable
}

define internal i32 @"PuppetPool::PuppetPool::function::v_call_IERC20_balanceOf__IERC20_address"([20 x i8] %0, [20 x i8] %1, i256* %2) {
entry:
  %stack = alloca i256, align 8
  %bytes4 = alloca i32, align 4
  %3 = call i8* @__malloc(i32 add (i32 ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32), i32 36))
  %string = bitcast i8* %3 to %struct.vector*
  %data_len = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 0
  store i32 36, i32* %data_len, align 4
  %data_size = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 1
  store i32 36, i32* %data_size, align 4
  %data = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 2
  %4 = bitcast [0 x i8]* %data to i8*
  store i32 1889567281, i32* %bytes4, align 4
  %store = bitcast i32* %bytes4 to i8*
  call void @__leNtobeN(i8* %store, i8* %4, i32 4)
  %5 = getelementptr i8, i8* %4, i32 4
  call void @__bzero8(i8* %5, i32 4)
  %6 = getelementptr i8, i8* %5, i32 32
  %address_ptr = getelementptr i8, i8* %5, i32 12
  %address_ptr1 = bitcast i8* %address_ptr to [20 x i8]*
  store [20 x i8] %1, [20 x i8]* %address_ptr1, align 1
  %7 = getelementptr i8, i8* %5, i32 32
  %address = alloca i8, i32 20, align 1
  %address2 = bitcast i8* %address to [20 x i8]*
  store [20 x i8] %0, [20 x i8]* %address2, align 1
  %data3 = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 2
  %data4 = bitcast [0 x i8]* %data3 to i8*
  %vector_len = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 0
  %vector_is_null = icmp eq %struct.vector* %string, null
  %vector_len5 = load i32, i32* %vector_len, align 4
  %length = select i1 %vector_is_null, i32 0, i32 %vector_len5
  %balance = alloca i128, align 8
  store i128 0, i128* %balance, align 8
  %value_transfer = bitcast i128* %balance to i8*
  %8 = call i32 @call(i64 9223372036854775807, i8* %address, i8* %value_transfer, i8* %data4, i32 %length)
  %success = icmp eq i32 %8, 0
  br i1 %success, label %success6, label %bail

success6:                                         ; preds = %entry
  %returndatasize = call i32 @getReturnDataSize()
  %size = add i32 %returndatasize, ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32)
  %9 = call i8* @__malloc(i32 %size)
  %string7 = bitcast i8* %9 to %struct.vector*
  %data_len8 = getelementptr %struct.vector, %struct.vector* %string7, i32 0, i32 0
  store i32 %returndatasize, i32* %data_len8, align 4
  %data_size9 = getelementptr %struct.vector, %struct.vector* %string7, i32 0, i32 1
  store i32 %returndatasize, i32* %data_size9, align 4
  %data10 = getelementptr %struct.vector, %struct.vector* %string7, i32 0, i32 2
  %10 = bitcast [0 x i8]* %data10 to i8*
  call void @returnDataCopy(i8* %10, i32 0, i32 %returndatasize)
  %data11 = getelementptr %struct.vector, %struct.vector* %string7, i32 0, i32 2
  %data12 = bitcast [0 x i8]* %data11 to i8*
  %vector_len13 = getelementptr %struct.vector, %struct.vector* %string7, i32 0, i32 0
  %vector_is_null14 = icmp eq %struct.vector* %string7, null
  %vector_len15 = load i32, i32* %vector_len13, align 4
  %length16 = select i1 %vector_is_null14, i32 0, i32 %vector_len15
  %data_length = zext i32 %length16 to i64
  %11 = icmp ule i64 32, %data_length
  br i1 %11, label %success17, label %bail18

bail:                                             ; preds = %entry
  call void @revert(i8* null, i32 0)
  unreachable

success17:                                        ; preds = %success6
  %12 = getelementptr i8, i8* %data12, i64 0
  %13 = bitcast i256* %stack to i8*
  call void @__be32toleN(i8* %12, i8* %13, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int256 = load i256, i256* %stack, align 8
  store i256 %abi_int256, i256* %2, align 8
  ret i32 0

bail18:                                           ; preds = %success6
  call void @revert(i8* null, i32 0)
  unreachable
}

define internal i32 @"PuppetPool::PuppetPool::function::_computeOraclePrice"(i256* %0) {
entry:
  %quotient = alloca i256, align 8
  %remainder = alloca i256, align 8
  %divisor = alloca i256, align 8
  %dividend = alloca i256, align 8
  %1 = alloca i256, align 8
  %2 = alloca i256, align 8
  %3 = alloca i256, align 8
  %slot = alloca i256, align 8
  store i256 2, i256* %slot, align 8
  %buf = alloca i8, i32 32, align 1
  %4 = bitcast i256* %slot to i8*
  call void @storageLoad(i8* %4, i8* %buf)
  %5 = bitcast i8* %buf to [20 x i8]*
  %loaded_address = load [20 x i8], [20 x i8]* %5, align 1
  %slot1 = alloca i256, align 8
  store i256 3, i256* %slot1, align 8
  %buf2 = alloca i8, i32 32, align 1
  %6 = bitcast i256* %slot1 to i8*
  call void @storageLoad(i8* %6, i8* %buf2)
  %7 = bitcast i8* %buf2 to [20 x i8]*
  %loaded_address3 = load [20 x i8], [20 x i8]* %7, align 1
  %8 = alloca i256, align 8
  %9 = call i32 @"PuppetPool::PuppetPool::function::v_call_IERC20_balanceOf__IERC20_address"([20 x i8] %loaded_address3, [20 x i8] %loaded_address, i256* %8)
  %success = icmp eq i32 %9, 0
  br i1 %success, label %success4, label %bail

success4:                                         ; preds = %entry
  %10 = load i256, i256* %8, align 8
  %address = alloca [20 x i8], align 1
  store [20 x i8] %loaded_address, [20 x i8]* %address, align 1
  %balance = alloca i128, align 8
  %11 = bitcast [20 x i8]* %address to i8*
  %12 = bitcast i128* %balance to i8*
  call void @getExternalBalance(i8* %11, i8* %12)
  %balance5 = load i128, i128* %balance, align 8
  %13 = sext i128 %balance5 to i256
  store i256 %13, i256* %3, align 8
  store i256 1000000000000000000, i256* %2, align 8
  %left = bitcast i256* %3 to i32*
  %right = bitcast i256* %2 to i32*
  %output = bitcast i256* %1 to i32*
  call void @__mul32(i32* %left, i32* %right, i32* %output, i32 8)
  %mul = load i256, i256* %1, align 8
  store i256 %mul, i256* %dividend, align 8
  store i256 %10, i256* %divisor, align 8
  %udiv = call i32 @udivmod256(i256* %dividend, i256* %divisor, i256* %remainder, i256* %quotient)
  %success6 = icmp eq i32 %udiv, 0
  br i1 %success6, label %success7, label %bail8

bail:                                             ; preds = %entry
  ret i32 %9

success7:                                         ; preds = %success4
  %quotient9 = load i256, i256* %quotient, align 8
  store i256 %quotient9, i256* %0, align 8
  ret i32 0

bail8:                                            ; preds = %success4
  call void @revert(i8* null, i32 0)
  unreachable
}

define internal i32 @"PuppetPool::PuppetPool::function::borrow__uint256"(i256 %0) {
entry:
  %uint3292 = alloca i32, align 4
  %uint3286 = alloca i32, align 4
  %uint3284 = alloca i32, align 4
  %bytes32 = alloca i256, align 8
  %uint25673 = alloca i256, align 8
  %uint25671 = alloca i256, align 8
  %uint256 = alloca i256, align 8
  %bytes4 = alloca i32, align 4
  %1 = alloca i256, align 8
  %uint3212 = alloca i32, align 4
  %uint326 = alloca i32, align 4
  %uint32 = alloca i32, align 4
  %2 = alloca i256, align 8
  %3 = call i32 @"PuppetPool::PuppetPool::function::calculateDepositRequired__uint256"(i256 %0, i256* %2)
  %success = icmp eq i32 %3, 0
  br i1 %success, label %success1, label %bail

success1:                                         ; preds = %entry
  %4 = load i256, i256* %2, align 8
  %value = alloca i128, align 8
  %5 = bitcast i128* %value to i8*
  call void @getCallValue(i8* %5)
  %value2 = load i128, i128* %value, align 8
  %6 = sext i128 %value2 to i256
  %7 = icmp uge i256 %6, %4
  br i1 %7, label %noassert, label %doassert

bail:                                             ; preds = %entry
  ret i32 %3

noassert:                                         ; preds = %success1
  %value3 = alloca i128, align 8
  %8 = bitcast i128* %value3 to i8*
  call void @getCallValue(i8* %8)
  %value4 = load i128, i128* %value3, align 8
  %9 = sext i128 %value4 to i256
  %10 = icmp ugt i256 %9, %4
  br i1 %10, label %then, label %endif

doassert:                                         ; preds = %success1
  %11 = call %struct.vector.0* @vector_new(i32 32, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([32 x i8], [32 x i8]* @const_string.3, i32 0, i32 0))
  %vector = bitcast %struct.vector.0* %11 to %struct.vector*
  %vector_len = getelementptr %struct.vector, %struct.vector* %vector, i32 0, i32 0
  %vector_is_null = icmp eq %struct.vector* %vector, null
  %vector_len5 = load i32, i32* %vector_len, align 4
  %length = select i1 %vector_is_null, i32 0, i32 %vector_len5
  %12 = add i32 %length, 63
  %13 = and i32 %12, -32
  %14 = add i32 36, %13
  %15 = call i8* @__malloc(i32 %14)
  store i32 147028384, i32* %uint32, align 4
  %store = bitcast i32* %uint32 to i8*
  call void @__leNtobeN(i8* %store, i8* %15, i32 4)
  %16 = getelementptr i8, i8* %15, i32 4
  %17 = udiv i32 %14, 8
  call void @__bzero8(i8* %16, i32 %17)
  %18 = getelementptr i8, i8* %16, i32 32
  store i32 32, i32* %uint326, align 4
  %store7 = bitcast i32* %uint326 to i8*
  call void @__leNtobe32(i8* %store7, i8* %16, i32 4)
  %19 = getelementptr i8, i8* %16, i32 32
  %vector_len8 = getelementptr %struct.vector, %struct.vector* %vector, i32 0, i32 0
  %vector_is_null9 = icmp eq %struct.vector* %vector, null
  %vector_len10 = load i32, i32* %vector_len8, align 4
  %length11 = select i1 %vector_is_null9, i32 0, i32 %vector_len10
  store i32 %length11, i32* %uint3212, align 4
  %store13 = bitcast i32* %uint3212 to i8*
  call void @__leNtobe32(i8* %store13, i8* %18, i32 4)
  %20 = getelementptr i8, i8* %18, i32 32
  %data = getelementptr %struct.vector, %struct.vector* %vector, i32 0, i32 2
  %data14 = bitcast [0 x i8]* %data to i8*
  call void @__memcpy(i8* %20, i8* %data14, i32 %length11)
  %21 = add i32 %length11, 31
  %22 = and i32 %21, -32
  %23 = getelementptr i8, i8* %20, i32 %22
  %24 = add i32 64, %22
  call void @revert(i8* %15, i32 %14)
  unreachable

then:                                             ; preds = %noassert
  %caller = alloca [20 x i8], align 1
  %25 = bitcast [20 x i8]* %caller to i8*
  call void @getCaller(i8* %25)
  %caller15 = load [20 x i8], [20 x i8]* %caller, align 1
  %value16 = alloca i128, align 8
  %26 = bitcast i128* %value16 to i8*
  call void @getCallValue(i8* %26)
  %value17 = load i128, i128* %value16, align 8
  %27 = sext i128 %value17 to i256
  %28 = sub i256 %27, %4
  %29 = call i32 @"PuppetPool::Address::function::sendValue__address_uint256"([20 x i8] %caller15, i256 %28)
  %success18 = icmp eq i32 %29, 0
  br i1 %success18, label %success19, label %bail20

endif:                                            ; preds = %success19, %noassert
  %caller21 = alloca [20 x i8], align 1
  %30 = bitcast [20 x i8]* %caller21 to i8*
  call void @getCaller(i8* %30)
  %caller22 = load [20 x i8], [20 x i8]* %caller21, align 1
  %keccak_src = alloca i8, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)), align 1
  %elem = getelementptr i8, i8* %keccak_src, i32 0
  %31 = bitcast i8* %elem to i256*
  store i256 1, i256* %31, align 8
  %elem23 = getelementptr i8, i8* %keccak_src, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32)
  %32 = bitcast i8* %elem23 to [20 x i8]*
  store [20 x i8] %caller22, [20 x i8]* %32, align 1
  %keccak_dst = alloca i256, align 8
  %balance = alloca i128, align 8
  store i128 0, i128* %balance, align 8
  %balance24 = bitcast i128* %balance to i8*
  %33 = call i32 @call(i64 9223372036854775807, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @keccak256_precompile.4, i32 0, i32 0), i8* %balance24, i8* %keccak_src, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)))
  %dest = bitcast i256* %keccak_dst to i8*
  call void @returnDataCopy(i8* %dest, i32 0, i32 32)
  %keccak256_hash = load i256, i256* %keccak_dst, align 8
  %slot = alloca i256, align 8
  store i256 %keccak256_hash, i256* %slot, align 8
  %buf = alloca i8, i32 32, align 1
  %34 = bitcast i256* %slot to i8*
  call void @storageLoad(i8* %34, i8* %buf)
  %35 = bitcast i8* %buf to i256*
  %loaded_int = load i256, i256* %35, align 8
  %int = add i256 %keccak256_hash, 1
  %36 = add i256 %loaded_int, %4
  %caller25 = alloca [20 x i8], align 1
  %37 = bitcast [20 x i8]* %caller25 to i8*
  call void @getCaller(i8* %37)
  %caller26 = load [20 x i8], [20 x i8]* %caller25, align 1
  %keccak_src27 = alloca i8, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)), align 1
  %elem28 = getelementptr i8, i8* %keccak_src27, i32 0
  %38 = bitcast i8* %elem28 to i256*
  store i256 1, i256* %38, align 8
  %elem29 = getelementptr i8, i8* %keccak_src27, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32)
  %39 = bitcast i8* %elem29 to [20 x i8]*
  store [20 x i8] %caller26, [20 x i8]* %39, align 1
  %keccak_dst30 = alloca i256, align 8
  %balance31 = alloca i128, align 8
  store i128 0, i128* %balance31, align 8
  %balance32 = bitcast i128* %balance31 to i8*
  %40 = call i32 @call(i64 9223372036854775807, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @keccak256_precompile.5, i32 0, i32 0), i8* %balance32, i8* %keccak_src27, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)))
  %dest33 = bitcast i256* %keccak_dst30 to i8*
  call void @returnDataCopy(i8* %dest33, i32 0, i32 32)
  %keccak256_hash34 = load i256, i256* %keccak_dst30, align 8
  %slot35 = alloca i256, align 8
  store i256 %keccak256_hash34, i256* %slot35, align 8
  store i256 %36, i256* %1, align 8
  %41 = bitcast i256* %slot35 to i8*
  %42 = bitcast i256* %1 to i8*
  call void @storageStore(i8* %41, i8* %42)
  %slot36 = alloca i256, align 8
  store i256 3, i256* %slot36, align 8
  %buf37 = alloca i8, i32 32, align 1
  %43 = bitcast i256* %slot36 to i8*
  call void @storageLoad(i8* %43, i8* %buf37)
  %44 = bitcast i8* %buf37 to [20 x i8]*
  %loaded_address = load [20 x i8], [20 x i8]* %44, align 1
  %caller38 = alloca [20 x i8], align 1
  %45 = bitcast [20 x i8]* %caller38 to i8*
  call void @getCaller(i8* %45)
  %caller39 = load [20 x i8], [20 x i8]* %caller38, align 1
  %46 = call i8* @__malloc(i32 add (i32 ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32), i32 68))
  %string = bitcast i8* %46 to %struct.vector*
  %data_len = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 0
  store i32 68, i32* %data_len, align 4
  %data_size = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 1
  store i32 68, i32* %data_size, align 4
  %data40 = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 2
  %47 = bitcast [0 x i8]* %data40 to i8*
  store i32 -1459249989, i32* %bytes4, align 4
  %store41 = bitcast i32* %bytes4 to i8*
  call void @__leNtobeN(i8* %store41, i8* %47, i32 4)
  %48 = getelementptr i8, i8* %47, i32 4
  call void @__bzero8(i8* %48, i32 8)
  %49 = getelementptr i8, i8* %48, i32 64
  %address_ptr = getelementptr i8, i8* %48, i32 12
  %address_ptr42 = bitcast i8* %address_ptr to [20 x i8]*
  store [20 x i8] %caller39, [20 x i8]* %address_ptr42, align 1
  %50 = getelementptr i8, i8* %48, i32 32
  store i256 %0, i256* %uint256, align 8
  %store43 = bitcast i256* %uint256 to i8*
  call void @__leNtobe32(i8* %store43, i8* %50, i32 32)
  %51 = getelementptr i8, i8* %50, i32 32
  %address = alloca i8, i32 20, align 1
  %address44 = bitcast i8* %address to [20 x i8]*
  store [20 x i8] %loaded_address, [20 x i8]* %address44, align 1
  %data45 = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 2
  %data46 = bitcast [0 x i8]* %data45 to i8*
  %vector_len47 = getelementptr %struct.vector, %struct.vector* %string, i32 0, i32 0
  %vector_is_null48 = icmp eq %struct.vector* %string, null
  %vector_len49 = load i32, i32* %vector_len47, align 4
  %length50 = select i1 %vector_is_null48, i32 0, i32 %vector_len49
  %balance51 = alloca i128, align 8
  store i128 0, i128* %balance51, align 8
  %value_transfer = bitcast i128* %balance51 to i8*
  %52 = call i32 @call(i64 9223372036854775807, i8* %address, i8* %value_transfer, i8* %data46, i32 %length50)
  %success52 = icmp eq i32 %52, 0
  br i1 %success52, label %success53, label %bail54

success19:                                        ; preds = %then
  br label %endif

bail20:                                           ; preds = %then
  ret i32 %29

success53:                                        ; preds = %endif
  %returndatasize = call i32 @getReturnDataSize()
  %size = add i32 %returndatasize, ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32)
  %53 = call i8* @__malloc(i32 %size)
  %string55 = bitcast i8* %53 to %struct.vector*
  %data_len56 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 0
  store i32 %returndatasize, i32* %data_len56, align 4
  %data_size57 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 1
  store i32 %returndatasize, i32* %data_size57, align 4
  %data58 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 2
  %54 = bitcast [0 x i8]* %data58 to i8*
  call void @returnDataCopy(i8* %54, i32 0, i32 %returndatasize)
  %data59 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 2
  %data60 = bitcast [0 x i8]* %data59 to i8*
  %vector_len61 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 0
  %vector_is_null62 = icmp eq %struct.vector* %string55, null
  %vector_len63 = load i32, i32* %vector_len61, align 4
  %length64 = select i1 %vector_is_null62, i32 0, i32 %vector_len63
  %data_length = zext i32 %length64 to i64
  %55 = icmp ule i64 32, %data_length
  br i1 %55, label %success65, label %bail66

bail54:                                           ; preds = %endif
  call void @revert(i8* null, i32 0)
  unreachable

success65:                                        ; preds = %success53
  %56 = getelementptr i8, i8* %data60, i64 0
  %57 = bitcast i8* %56 to i64*
  %bool_ptr = getelementptr i64, i64* %57, i32 3
  %abi_bool = load i64, i64* %bool_ptr, align 8
  %bool = icmp ne i64 %abi_bool, 0
  br i1 %bool, label %noassert67, label %doassert68

bail66:                                           ; preds = %success53
  call void @revert(i8* null, i32 0)
  unreachable

noassert67:                                       ; preds = %success65
  %caller69 = alloca [20 x i8], align 1
  %58 = bitcast [20 x i8]* %caller69 to i8*
  call void @getCaller(i8* %58)
  %caller70 = load [20 x i8], [20 x i8]* %caller69, align 1
  %59 = call i8* @__malloc(i32 64)
  call void @__bzero8(i8* %59, i32 8)
  %60 = getelementptr i8, i8* %59, i32 64
  store i256 %4, i256* %uint25671, align 8
  %store72 = bitcast i256* %uint25671 to i8*
  call void @__leNtobe32(i8* %store72, i8* %59, i32 32)
  %61 = getelementptr i8, i8* %59, i32 32
  store i256 %0, i256* %uint25673, align 8
  %store74 = bitcast i256* %uint25673 to i8*
  call void @__leNtobe32(i8* %store74, i8* %61, i32 32)
  %62 = getelementptr i8, i8* %61, i32 32
  %63 = call i8* @__malloc(i32 64)
  call void @__bzero8(i8* %63, i32 8)
  %64 = getelementptr i8, i8* %63, i32 64
  store i256 -9537773560138156302262374008369018912504308177848412795308944527167260367056, i256* %bytes32, align 8
  %store75 = bitcast i256* %bytes32 to i8*
  call void @__leNtobeN(i8* %store75, i8* %63, i32 32)
  %65 = getelementptr i8, i8* %63, i32 32
  %address_ptr76 = getelementptr i8, i8* %65, i32 12
  %address_ptr77 = bitcast i8* %address_ptr76 to [20 x i8]*
  store [20 x i8] %caller70, [20 x i8]* %address_ptr77, align 1
  %66 = getelementptr i8, i8* %65, i32 32
  %next_topic = getelementptr i8, i8* %63, i32 32
  %next_topic78 = getelementptr i8, i8* %next_topic, i32 32
  call void @log(i8* %59, i32 64, i32 2, i8* %63, i8* %next_topic, i8* null, i8* null)
  ret i32 0

doassert68:                                       ; preds = %success65
  %67 = call %struct.vector.0* @vector_new(i32 15, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @const_string.6, i32 0, i32 0))
  %vector79 = bitcast %struct.vector.0* %67 to %struct.vector*
  %vector_len80 = getelementptr %struct.vector, %struct.vector* %vector79, i32 0, i32 0
  %vector_is_null81 = icmp eq %struct.vector* %vector79, null
  %vector_len82 = load i32, i32* %vector_len80, align 4
  %length83 = select i1 %vector_is_null81, i32 0, i32 %vector_len82
  %68 = add i32 %length83, 63
  %69 = and i32 %68, -32
  %70 = add i32 36, %69
  %71 = call i8* @__malloc(i32 %70)
  store i32 147028384, i32* %uint3284, align 4
  %store85 = bitcast i32* %uint3284 to i8*
  call void @__leNtobeN(i8* %store85, i8* %71, i32 4)
  %72 = getelementptr i8, i8* %71, i32 4
  %73 = udiv i32 %70, 8
  call void @__bzero8(i8* %72, i32 %73)
  %74 = getelementptr i8, i8* %72, i32 32
  store i32 32, i32* %uint3286, align 4
  %store87 = bitcast i32* %uint3286 to i8*
  call void @__leNtobe32(i8* %store87, i8* %72, i32 4)
  %75 = getelementptr i8, i8* %72, i32 32
  %vector_len88 = getelementptr %struct.vector, %struct.vector* %vector79, i32 0, i32 0
  %vector_is_null89 = icmp eq %struct.vector* %vector79, null
  %vector_len90 = load i32, i32* %vector_len88, align 4
  %length91 = select i1 %vector_is_null89, i32 0, i32 %vector_len90
  store i32 %length91, i32* %uint3292, align 4
  %store93 = bitcast i32* %uint3292 to i8*
  call void @__leNtobe32(i8* %store93, i8* %74, i32 4)
  %76 = getelementptr i8, i8* %74, i32 32
  %data94 = getelementptr %struct.vector, %struct.vector* %vector79, i32 0, i32 2
  %data95 = bitcast [0 x i8]* %data94 to i8*
  call void @__memcpy(i8* %76, i8* %data95, i32 %length91)
  %77 = add i32 %length91, 31
  %78 = and i32 %77, -32
  %79 = getelementptr i8, i8* %76, i32 %78
  %80 = add i32 64, %78
  call void @revert(i8* %71, i32 %70)
  unreachable
}

define internal i32 @"PuppetPool:storage_initializer"() {
entry:
  ret i32 0
}

define internal i32 @"sol::PuppetPool::storage_initializers"() {
entry:
  ret i32 0
}

define void @main() {
entry:
  %value_transferred = alloca i128, align 8
  %0 = bitcast i128* %value_transferred to i8*
  call void @getCallValue(i8* %0)
  %value_transferred1 = load i128, i128* %value_transferred, align 8
  %is_value_transfer = icmp ne i128 %value_transferred1, 0
  br i1 %is_value_transfer, label %abort_value_transfer, label %not_value_transfer

not_value_transfer:                               ; preds = %entry
  call void @__init_heap()
  %codesize = call i32 @getCodeSize()
  %1 = sub i32 %codesize, 16384
  store i32 %1, i32* @calldata_len, align 4
  %2 = call i8* @__malloc(i32 %1)
  store i8* %2, i8** @calldata_data, align 4
  call void @codeCopy(i8* %2, i32 16384, i32 %1)
  %3 = bitcast i8* %2 to i32*
  %4 = call i32 @"sol::PuppetPool::storage_initializers"()
  %data = bitcast i32* %3 to i8*
  %data_length = zext i32 %1 to i64
  %5 = call i32 @"PuppetPool::ReentrancyGuard::constructor::861731d5"()
  call void @finish(i8* getelementptr inbounds ([13887 x i8], [13887 x i8]* @runtime_code, i32 0, i32 0), i32 13887)
  unreachable

abort_value_transfer:                             ; preds = %entry
  call void @revert(i8* null, i32 0)
  unreachable
}

attributes #0 = { nofree norecurse nosync nounwind writeonly "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" }
attributes #1 = { nofree norecurse nosync nounwind "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" }
attributes #2 = { nofree norecurse nosync nounwind readonly "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" }
attributes #4 = { noinline nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { inaccessiblememonly nofree nosync nounwind willreturn }
attributes #6 = { nofree nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly }
attributes #8 = { nofree noinline norecurse nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #10 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #11 = { norecurse nounwind readnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #12 = { nofree norecurse nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #13 = { norecurse nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #14 = { nounwind writeonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #15 = { argmemonly nofree nosync nounwind willreturn }
attributes #16 = { noreturn }
attributes #17 = { nobuiltin nounwind "no-builtins" }
attributes #18 = { nobuiltin "no-builtins" }
attributes #19 = { nounwind }

!llvm.ident = !{!0, !1, !2, !2}
!llvm.module.flags = !{!3}

!0 = !{!"clang version 13.0.0 (https://github.com/solana-labs/llvm-project 9743d18ce86564710488a1cd6438f09e95f17b3f)"}
!1 = !{!"clang version 11.0.1 (git://github.com/llvm/llvm-project 13e4369c73355a6c5a31fc1a1115fc7c69743ada)"}
!2 = !{!"clang version 11.0.1 (git://github.com/llvm/llvm-project 852f4d8eb6d317be0947055c0bb6b4fd6c9aa930)"}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{!5, !5, i64 0}
!5 = !{!"long long", !6, i64 0}
!6 = !{!"omnipotent char", !7, i64 0}
!7 = !{!"Simple C/C++ TBAA"}
!8 = distinct !{!8, !9}
!9 = !{!"llvm.loop.unroll.disable"}
!10 = distinct !{!10, !11}
!11 = !{!"llvm.loop.mustprogress"}
!12 = !{!6, !6, i64 0}
!13 = distinct !{!13, !9}
!14 = distinct !{!14, !11}
!15 = distinct !{!15, !9}
!16 = distinct !{!16, !11}
!17 = distinct !{!17, !9}
!18 = distinct !{!18, !11}
!19 = distinct !{!19, !9}
!20 = distinct !{!20, !11}
!21 = distinct !{!21, !11}
!22 = distinct !{!22, !9}
!23 = distinct !{!23, !11}
!24 = distinct !{!24, !9}
!25 = distinct !{!25, !11}
!26 = distinct !{!26, !9}
!27 = distinct !{!27, !11}
!28 = distinct !{!28, !9}
!29 = distinct !{!29, !11}
!30 = !{!31, !31, i64 0}
!31 = !{!"int", !6, i64 0}
!32 = distinct !{!32, !9}
!33 = distinct !{!33, !9}
!34 = distinct !{!34, !11}
!35 = distinct !{!35, !11}
!36 = !{!37, !39, i64 12}
!37 = !{!"chunk", !38, i64 0, !38, i64 4, !39, i64 8, !39, i64 12}
!38 = !{!"any pointer", !6, i64 0}
!39 = !{!"long", !6, i64 0}
!40 = !{!37, !39, i64 8}
!41 = !{!37, !38, i64 0}
!42 = !{!37, !38, i64 4}
!43 = distinct !{!43, !11}
!44 = distinct !{!44, !9}
!45 = distinct !{!45, !9}
!46 = distinct !{!46, !11}
!47 = distinct !{!47, !11}
!48 = !{!49, !49, i64 0}
!49 = !{!"__int128", !6, i64 0}
!50 = !{!51, !51, i64 0}
!51 = !{!"_ExtInt(256)", !6, i64 0}
!52 = !{!53, !53, i64 0}
!53 = !{!"_ExtInt(512)", !6, i64 0}
