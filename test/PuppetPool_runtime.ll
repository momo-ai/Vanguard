; ModuleID = 'PuppetPool'
source_filename = "Pool.sol"
target datalayout = "e-m:e-p:32:32-i64:64-n32:64-S128-ni:1:10:20"
target triple = "wasm32-unknown-unknown-wasm"

%struct.vector = type { i32, i32, [0 x i8] }
%struct.chunk = type { %struct.chunk*, %struct.chunk*, i32, i32 }

@uint256_0 = hidden local_unnamed_addr constant i256 0, align 8
@uint256_1 = hidden local_unnamed_addr constant i256 1, align 8
@uint512_0 = hidden local_unnamed_addr constant i512 0, align 8
@uint512_1 = hidden local_unnamed_addr constant i512 1, align 8
@selector = internal global i32 0
@calldata_len = internal global i32 0
@calldata_data = internal global i8* null
@const_string = internal unnamed_addr constant [29 x i8] c"Address: insufficient balance"
@const_string.1 = internal unnamed_addr constant [58 x i8] c"Address: unable to send value, recipient may have reverted"
@const_string.2 = internal unnamed_addr constant [31 x i8] c"ReentrancyGuard: reentrant call"
@const_string.3 = internal unnamed_addr constant [32 x i8] c"Not depositing enough collateral"
@keccak256_precompile.5 = internal unnamed_addr constant [20 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\14"
@const_string.6 = internal unnamed_addr constant [15 x i8] c"Transfer failed"

; Function Attrs: nofree norecurse nosync nounwind writeonly
define hidden void @__memset8(i8* nocapture %_dest, i64 %val, i32 %length) local_unnamed_addr #0 {
entry:
  %0 = bitcast i8* %_dest to i64*
  %1 = add i32 %length, -1
  %xtraiter = and i32 %length, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  %2 = bitcast i8* %_dest to i64*
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %dest.0.prol = phi i64* [ %incdec.ptr.prol, %do.body.prol ], [ %2, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
  %incdec.ptr.prol = getelementptr inbounds i64, i64* %dest.0.prol, i32 1
  store i64 %val, i64* %dest.0.prol, align 8, !tbaa !4
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !8

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %dest.0.unr = phi i64* [ %0, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %3 = icmp ult i32 %1, 7
  br i1 %3, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %length.addr.0 = phi i32 [ %dec.7, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %dest.0 = phi i64* [ %scevgep7, %do.body ], [ %dest.0.unr, %do.body.preheader ]
  store i64 %val, i64* %dest.0, align 8, !tbaa !4
  %scevgep = getelementptr i64, i64* %dest.0, i32 1
  store i64 %val, i64* %scevgep, align 8, !tbaa !4
  %scevgep1 = getelementptr i64, i64* %dest.0, i32 2
  store i64 %val, i64* %scevgep1, align 8, !tbaa !4
  %scevgep2 = getelementptr i64, i64* %dest.0, i32 3
  store i64 %val, i64* %scevgep2, align 8, !tbaa !4
  %scevgep3 = getelementptr i64, i64* %dest.0, i32 4
  store i64 %val, i64* %scevgep3, align 8, !tbaa !4
  %scevgep4 = getelementptr i64, i64* %dest.0, i32 5
  store i64 %val, i64* %scevgep4, align 8, !tbaa !4
  %scevgep5 = getelementptr i64, i64* %dest.0, i32 6
  store i64 %val, i64* %scevgep5, align 8, !tbaa !4
  %scevgep6 = getelementptr i64, i64* %dest.0, i32 7
  store i64 %val, i64* %scevgep6, align 8, !tbaa !4
  %dec.7 = add i32 %length.addr.0, -8
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep7 = getelementptr i64, i64* %dest.0, i32 8
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
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %dest.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %_dest, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
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
  br i1 %1, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %length.addr.0 = phi i32 [ %dec.7, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %dest.0 = phi i8* [ %scevgep7, %do.body ], [ %dest.0.unr, %do.body.preheader ]
  store i8 %val, i8* %dest.0, align 1, !tbaa !12
  %scevgep = getelementptr i8, i8* %dest.0, i32 1
  store i8 %val, i8* %scevgep, align 1, !tbaa !12
  %scevgep1 = getelementptr i8, i8* %dest.0, i32 2
  store i8 %val, i8* %scevgep1, align 1, !tbaa !12
  %scevgep2 = getelementptr i8, i8* %dest.0, i32 3
  store i8 %val, i8* %scevgep2, align 1, !tbaa !12
  %scevgep3 = getelementptr i8, i8* %dest.0, i32 4
  store i8 %val, i8* %scevgep3, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %dest.0, i32 5
  store i8 %val, i8* %scevgep4, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %dest.0, i32 6
  store i8 %val, i8* %scevgep5, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %dest.0, i32 7
  store i8 %val, i8* %scevgep6, align 1, !tbaa !12
  %dec.7 = add i32 %length.addr.0, -8
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep7 = getelementptr i8, i8* %dest.0, i32 8
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
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  %3 = bitcast i8* %_src to i64*
  %4 = bitcast i8* %_dest to i64*
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %dest.0.prol = phi i64* [ %incdec.ptr1.prol, %do.body.prol ], [ %4, %do.body.prol.preheader ]
  %src.0.prol = phi i64* [ %incdec.ptr.prol, %do.body.prol ], [ %3, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
  %incdec.ptr.prol = getelementptr inbounds i64, i64* %src.0.prol, i32 1
  %5 = load i64, i64* %src.0.prol, align 8, !tbaa !4
  %incdec.ptr1.prol = getelementptr inbounds i64, i64* %dest.0.prol, i32 1
  store i64 %5, i64* %dest.0.prol, align 8, !tbaa !4
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit, label %do.body.prol, !llvm.loop !15

do.body.prol.loopexit:                            ; preds = %do.body.prol, %entry
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol ]
  %dest.0.unr = phi i64* [ %0, %entry ], [ %incdec.ptr1.prol, %do.body.prol ]
  %src.0.unr = phi i64* [ %1, %entry ], [ %incdec.ptr.prol, %do.body.prol ]
  %6 = icmp ult i32 %2, 7
  br i1 %6, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %length.addr.0 = phi i32 [ %dec.7, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %dest.0 = phi i64* [ %scevgep15, %do.body ], [ %dest.0.unr, %do.body.preheader ]
  %src.0 = phi i64* [ %scevgep7, %do.body ], [ %src.0.unr, %do.body.preheader ]
  %7 = load i64, i64* %src.0, align 8, !tbaa !4
  store i64 %7, i64* %dest.0, align 8, !tbaa !4
  %scevgep = getelementptr i64, i64* %src.0, i32 1
  %8 = load i64, i64* %scevgep, align 8, !tbaa !4
  %scevgep8 = getelementptr i64, i64* %dest.0, i32 1
  store i64 %8, i64* %scevgep8, align 8, !tbaa !4
  %scevgep1 = getelementptr i64, i64* %src.0, i32 2
  %9 = load i64, i64* %scevgep1, align 8, !tbaa !4
  %scevgep9 = getelementptr i64, i64* %dest.0, i32 2
  store i64 %9, i64* %scevgep9, align 8, !tbaa !4
  %scevgep2 = getelementptr i64, i64* %src.0, i32 3
  %10 = load i64, i64* %scevgep2, align 8, !tbaa !4
  %scevgep10 = getelementptr i64, i64* %dest.0, i32 3
  store i64 %10, i64* %scevgep10, align 8, !tbaa !4
  %scevgep3 = getelementptr i64, i64* %src.0, i32 4
  %11 = load i64, i64* %scevgep3, align 8, !tbaa !4
  %scevgep11 = getelementptr i64, i64* %dest.0, i32 4
  store i64 %11, i64* %scevgep11, align 8, !tbaa !4
  %scevgep4 = getelementptr i64, i64* %src.0, i32 5
  %12 = load i64, i64* %scevgep4, align 8, !tbaa !4
  %scevgep12 = getelementptr i64, i64* %dest.0, i32 5
  store i64 %12, i64* %scevgep12, align 8, !tbaa !4
  %scevgep5 = getelementptr i64, i64* %src.0, i32 6
  %13 = load i64, i64* %scevgep5, align 8, !tbaa !4
  %scevgep13 = getelementptr i64, i64* %dest.0, i32 6
  store i64 %13, i64* %scevgep13, align 8, !tbaa !4
  %scevgep6 = getelementptr i64, i64* %src.0, i32 7
  %14 = load i64, i64* %scevgep6, align 8, !tbaa !4
  %scevgep14 = getelementptr i64, i64* %dest.0, i32 7
  store i64 %14, i64* %scevgep14, align 8, !tbaa !4
  %dec.7 = add i32 %length.addr.0, -8
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep7 = getelementptr i64, i64* %src.0, i32 8
  %scevgep15 = getelementptr i64, i64* %dest.0, i32 8
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
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol.preheader

while.body.prol.preheader:                        ; preds = %while.body.preheader
  br label %while.body.prol

while.body.prol:                                  ; preds = %while.body.prol.preheader, %while.body.prol
  %src.07.prol = phi i8* [ %incdec.ptr.prol, %while.body.prol ], [ %_src, %while.body.prol.preheader ]
  %dest.06.prol = phi i8* [ %incdec.ptr1.prol, %while.body.prol ], [ %_dest, %while.body.prol.preheader ]
  %length.addr.05.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %length, %while.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.prol.preheader ]
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
  br i1 %2, label %while.end, label %while.body.preheader1

while.body.preheader1:                            ; preds = %while.body.prol.loopexit
  br label %while.body

while.body:                                       ; preds = %while.body.preheader1, %while.body
  %src.07 = phi i8* [ %scevgep8, %while.body ], [ %src.07.unr, %while.body.preheader1 ]
  %dest.06 = phi i8* [ %scevgep16, %while.body ], [ %dest.06.unr, %while.body.preheader1 ]
  %length.addr.05 = phi i32 [ %dec.7, %while.body ], [ %length.addr.05.unr, %while.body.preheader1 ]
  %3 = load i8, i8* %src.07, align 1, !tbaa !12
  store i8 %3, i8* %dest.06, align 1, !tbaa !12
  %scevgep = getelementptr i8, i8* %src.07, i32 1
  %4 = load i8, i8* %scevgep, align 1, !tbaa !12
  %scevgep9 = getelementptr i8, i8* %dest.06, i32 1
  store i8 %4, i8* %scevgep9, align 1, !tbaa !12
  %scevgep2 = getelementptr i8, i8* %src.07, i32 2
  %5 = load i8, i8* %scevgep2, align 1, !tbaa !12
  %scevgep10 = getelementptr i8, i8* %dest.06, i32 2
  store i8 %5, i8* %scevgep10, align 1, !tbaa !12
  %scevgep3 = getelementptr i8, i8* %src.07, i32 3
  %6 = load i8, i8* %scevgep3, align 1, !tbaa !12
  %scevgep11 = getelementptr i8, i8* %dest.06, i32 3
  store i8 %6, i8* %scevgep11, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %src.07, i32 4
  %7 = load i8, i8* %scevgep4, align 1, !tbaa !12
  %scevgep12 = getelementptr i8, i8* %dest.06, i32 4
  store i8 %7, i8* %scevgep12, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %src.07, i32 5
  %8 = load i8, i8* %scevgep5, align 1, !tbaa !12
  %scevgep13 = getelementptr i8, i8* %dest.06, i32 5
  store i8 %8, i8* %scevgep13, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %src.07, i32 6
  %9 = load i8, i8* %scevgep6, align 1, !tbaa !12
  %scevgep14 = getelementptr i8, i8* %dest.06, i32 6
  store i8 %9, i8* %scevgep14, align 1, !tbaa !12
  %dec.7 = add i32 %length.addr.05, -8
  %scevgep7 = getelementptr i8, i8* %src.07, i32 7
  %10 = load i8, i8* %scevgep7, align 1, !tbaa !12
  %scevgep15 = getelementptr i8, i8* %dest.06, i32 7
  store i8 %10, i8* %scevgep15, align 1, !tbaa !12
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep8 = getelementptr i8, i8* %src.07, i32 8
  %scevgep16 = getelementptr i8, i8* %dest.06, i32 8
  br i1 %tobool.not.7, label %while.end, label %while.body, !llvm.loop !18

while.end:                                        ; preds = %while.body, %while.body.prol.loopexit, %entry
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
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol.preheader

while.body.prol.preheader:                        ; preds = %while.body.preheader
  %2 = bitcast i8* %_dest to i64*
  br label %while.body.prol

while.body.prol:                                  ; preds = %while.body.prol.preheader, %while.body.prol
  %dest.04.prol = phi i64* [ %incdec.ptr.prol, %while.body.prol ], [ %2, %while.body.prol.preheader ]
  %length.addr.03.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %length, %while.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.prol.preheader ]
  %dec.prol = add i32 %length.addr.03.prol, -1
  %incdec.ptr.prol = getelementptr inbounds i64, i64* %dest.04.prol, i32 1
  store i64 0, i64* %dest.04.prol, align 8, !tbaa !4
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %while.body.prol.loopexit, label %while.body.prol, !llvm.loop !19

while.body.prol.loopexit:                         ; preds = %while.body.prol, %while.body.preheader
  %dest.04.unr = phi i64* [ %0, %while.body.preheader ], [ %incdec.ptr.prol, %while.body.prol ]
  %length.addr.03.unr = phi i32 [ %length, %while.body.preheader ], [ %dec.prol, %while.body.prol ]
  %3 = icmp ult i32 %1, 7
  br i1 %3, label %while.end, label %while.body.preheader1

while.body.preheader1:                            ; preds = %while.body.prol.loopexit
  br label %while.body

while.body:                                       ; preds = %while.body.preheader1, %while.body
  %dest.04 = phi i64* [ %scevgep8, %while.body ], [ %dest.04.unr, %while.body.preheader1 ]
  %length.addr.03 = phi i32 [ %dec.7, %while.body ], [ %length.addr.03.unr, %while.body.preheader1 ]
  store i64 0, i64* %dest.04, align 8, !tbaa !4
  %scevgep = getelementptr i64, i64* %dest.04, i32 1
  store i64 0, i64* %scevgep, align 8, !tbaa !4
  %scevgep2 = getelementptr i64, i64* %dest.04, i32 2
  store i64 0, i64* %scevgep2, align 8, !tbaa !4
  %scevgep3 = getelementptr i64, i64* %dest.04, i32 3
  store i64 0, i64* %scevgep3, align 8, !tbaa !4
  %scevgep4 = getelementptr i64, i64* %dest.04, i32 4
  store i64 0, i64* %scevgep4, align 8, !tbaa !4
  %scevgep5 = getelementptr i64, i64* %dest.04, i32 5
  store i64 0, i64* %scevgep5, align 8, !tbaa !4
  %scevgep6 = getelementptr i64, i64* %dest.04, i32 6
  store i64 0, i64* %scevgep6, align 8, !tbaa !4
  %dec.7 = add i32 %length.addr.03, -8
  %scevgep7 = getelementptr i64, i64* %dest.04, i32 7
  store i64 0, i64* %scevgep7, align 8, !tbaa !4
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep8 = getelementptr i64, i64* %dest.04, i32 8
  br i1 %tobool.not.7, label %while.end, label %while.body, !llvm.loop !20

while.end:                                        ; preds = %while.body, %while.body.prol.loopexit, %entry
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
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %add.ptr, %do.body.prol.preheader ]
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %to, %do.body.prol.preheader ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
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
  br i1 %2, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %from.addr.0 = phi i8* [ %scevgep3, %do.body ], [ %from.addr.0.unr, %do.body.preheader ]
  %to.addr.0 = phi i8* [ %scevgep7, %do.body ], [ %to.addr.0.unr, %do.body.preheader ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %3 = load i8, i8* %from.addr.0, align 1, !tbaa !12
  store i8 %3, i8* %to.addr.0, align 1, !tbaa !12
  %scevgep = getelementptr i8, i8* %from.addr.0, i32 -1
  %4 = load i8, i8* %scevgep, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %to.addr.0, i32 1
  store i8 %4, i8* %scevgep4, align 1, !tbaa !12
  %scevgep1 = getelementptr i8, i8* %scevgep, i32 -1
  %5 = load i8, i8* %scevgep1, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %to.addr.0, i32 2
  store i8 %5, i8* %scevgep5, align 1, !tbaa !12
  %scevgep2 = getelementptr i8, i8* %scevgep1, i32 -1
  %6 = load i8, i8* %scevgep2, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %to.addr.0, i32 3
  store i8 %6, i8* %scevgep6, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  %scevgep3 = getelementptr i8, i8* %scevgep2, i32 -1
  %scevgep7 = getelementptr i8, i8* %to.addr.0, i32 4
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
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %to, %do.body.prol.preheader ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
  %scevgep10 = getelementptr i8, i8* %from, i32 %length.addr.0.prol
  %scevgep11 = getelementptr i8, i8* %scevgep10, i32 -1
  %1 = load i8, i8* %scevgep11, align 1, !tbaa !12
  %incdec.ptr1.prol = getelementptr inbounds i8, i8* %to.addr.0.prol, i32 1
  store i8 %1, i8* %to.addr.0.prol, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit.loopexit, label %do.body.prol, !llvm.loop !24

do.body.prol.loopexit.loopexit:                   ; preds = %do.body.prol
  %scevgep9 = getelementptr i8, i8* %from, i32 %dec.prol
  br label %do.body.prol.loopexit

do.body.prol.loopexit:                            ; preds = %do.body.prol.loopexit.loopexit, %entry
  %from.addr.0.unr = phi i8* [ %add.ptr, %entry ], [ %scevgep9, %do.body.prol.loopexit.loopexit ]
  %to.addr.0.unr = phi i8* [ %to, %entry ], [ %incdec.ptr1.prol, %do.body.prol.loopexit.loopexit ]
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol.loopexit.loopexit ]
  %2 = icmp ult i32 %0, 3
  br i1 %2, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  %scevgep = getelementptr i8, i8* %from.addr.0.unr, i32 -4
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %lsr.iv = phi i8* [ %scevgep, %do.body.preheader ], [ %scevgep1, %do.body ]
  %to.addr.0 = phi i8* [ %scevgep8, %do.body ], [ %to.addr.0.unr, %do.body.preheader ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %scevgep4 = getelementptr i8, i8* %lsr.iv, i32 3
  %3 = load i8, i8* %scevgep4, align 1, !tbaa !12
  store i8 %3, i8* %to.addr.0, align 1, !tbaa !12
  %scevgep3 = getelementptr i8, i8* %lsr.iv, i32 2
  %4 = load i8, i8* %scevgep3, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %to.addr.0, i32 1
  store i8 %4, i8* %scevgep5, align 1, !tbaa !12
  %scevgep2 = getelementptr i8, i8* %lsr.iv, i32 1
  %5 = load i8, i8* %scevgep2, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %to.addr.0, i32 2
  store i8 %5, i8* %scevgep6, align 1, !tbaa !12
  %6 = load i8, i8* %lsr.iv, align 1, !tbaa !12
  %scevgep7 = getelementptr i8, i8* %to.addr.0, i32 3
  store i8 %6, i8* %scevgep7, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %scevgep1 = getelementptr i8, i8* %lsr.iv, i32 -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  %scevgep8 = getelementptr i8, i8* %to.addr.0, i32 4
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
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %from, %do.body.prol.preheader ]
  %to.addr.0.prol = phi i8* [ %incdec.ptr1.prol, %do.body.prol ], [ %add.ptr, %do.body.prol.preheader ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
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
  br i1 %2, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %from.addr.0 = phi i8* [ %scevgep3, %do.body ], [ %from.addr.0.unr, %do.body.preheader ]
  %to.addr.0 = phi i8* [ %scevgep7, %do.body ], [ %to.addr.0.unr, %do.body.preheader ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %3 = load i8, i8* %from.addr.0, align 1, !tbaa !12
  store i8 %3, i8* %to.addr.0, align 1, !tbaa !12
  %scevgep = getelementptr i8, i8* %from.addr.0, i32 1
  %4 = load i8, i8* %scevgep, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %to.addr.0, i32 -1
  store i8 %4, i8* %scevgep4, align 1, !tbaa !12
  %scevgep1 = getelementptr i8, i8* %from.addr.0, i32 2
  %5 = load i8, i8* %scevgep1, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %scevgep4, i32 -1
  store i8 %5, i8* %scevgep5, align 1, !tbaa !12
  %scevgep2 = getelementptr i8, i8* %from.addr.0, i32 3
  %6 = load i8, i8* %scevgep2, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %scevgep5, i32 -1
  store i8 %6, i8* %scevgep6, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  %scevgep3 = getelementptr i8, i8* %from.addr.0, i32 4
  %scevgep7 = getelementptr i8, i8* %scevgep6, i32 -1
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
  br i1 %lcmp.mod.not, label %do.body.prol.loopexit, label %do.body.prol.preheader

do.body.prol.preheader:                           ; preds = %entry
  br label %do.body.prol

do.body.prol:                                     ; preds = %do.body.prol.preheader, %do.body.prol
  %from.addr.0.prol = phi i8* [ %incdec.ptr.prol, %do.body.prol ], [ %from, %do.body.prol.preheader ]
  %length.addr.0.prol = phi i32 [ %dec.prol, %do.body.prol ], [ %length, %do.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %do.body.prol ], [ %xtraiter, %do.body.prol.preheader ]
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %from.addr.0.prol, i32 1
  %1 = load i8, i8* %from.addr.0.prol, align 1, !tbaa !12
  %scevgep10 = getelementptr i8, i8* %to, i32 %length.addr.0.prol
  %scevgep11 = getelementptr i8, i8* %scevgep10, i32 -1
  store i8 %1, i8* %scevgep11, align 1, !tbaa !12
  %dec.prol = add i32 %length.addr.0.prol, -1
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %do.body.prol.loopexit.loopexit, label %do.body.prol, !llvm.loop !28

do.body.prol.loopexit.loopexit:                   ; preds = %do.body.prol
  %scevgep9 = getelementptr i8, i8* %to, i32 %dec.prol
  br label %do.body.prol.loopexit

do.body.prol.loopexit:                            ; preds = %do.body.prol.loopexit.loopexit, %entry
  %from.addr.0.unr = phi i8* [ %from, %entry ], [ %incdec.ptr.prol, %do.body.prol.loopexit.loopexit ]
  %to.addr.0.unr = phi i8* [ %add.ptr, %entry ], [ %scevgep9, %do.body.prol.loopexit.loopexit ]
  %length.addr.0.unr = phi i32 [ %length, %entry ], [ %dec.prol, %do.body.prol.loopexit.loopexit ]
  %2 = icmp ult i32 %0, 3
  br i1 %2, label %do.end, label %do.body.preheader

do.body.preheader:                                ; preds = %do.body.prol.loopexit
  %scevgep = getelementptr i8, i8* %to.addr.0.unr, i32 -4
  br label %do.body

do.body:                                          ; preds = %do.body.preheader, %do.body
  %lsr.iv = phi i8* [ %scevgep, %do.body.preheader ], [ %scevgep1, %do.body ]
  %from.addr.0 = phi i8* [ %scevgep8, %do.body ], [ %from.addr.0.unr, %do.body.preheader ]
  %length.addr.0 = phi i32 [ %dec.3, %do.body ], [ %length.addr.0.unr, %do.body.preheader ]
  %3 = load i8, i8* %from.addr.0, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %lsr.iv, i32 3
  store i8 %3, i8* %scevgep4, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %from.addr.0, i32 1
  %4 = load i8, i8* %scevgep5, align 1, !tbaa !12
  %scevgep3 = getelementptr i8, i8* %lsr.iv, i32 2
  store i8 %4, i8* %scevgep3, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %from.addr.0, i32 2
  %5 = load i8, i8* %scevgep6, align 1, !tbaa !12
  %scevgep2 = getelementptr i8, i8* %lsr.iv, i32 1
  store i8 %5, i8* %scevgep2, align 1, !tbaa !12
  %scevgep7 = getelementptr i8, i8* %from.addr.0, i32 3
  %6 = load i8, i8* %scevgep7, align 1, !tbaa !12
  store i8 %6, i8* %lsr.iv, align 1, !tbaa !12
  %dec.3 = add i32 %length.addr.0, -4
  %scevgep1 = getelementptr i8, i8* %lsr.iv, i32 -4
  %tobool.not.3 = icmp eq i32 %dec.3, 0
  %scevgep8 = getelementptr i8, i8* %from.addr.0, i32 4
  br i1 %tobool.not.3, label %do.end, label %do.body, !llvm.loop !29

do.end:                                           ; preds = %do.body, %do.body.prol.loopexit
  ret void
}

; Function Attrs: nounwind
define hidden %struct.vector* @vector_new(i32 %members, i32 %size, i8* readonly %initial) local_unnamed_addr #3 {
entry:
  %mul = mul i32 %size, %members
  %add = add i32 %mul, 8
  %call = tail call i8* @__malloc(i32 %add) #18
  %len = bitcast i8* %call to i32*
  store i32 %members, i32* %len, align 4, !tbaa !30
  %size1 = getelementptr inbounds i8, i8* %call, i32 4
  %0 = bitcast i8* %size1 to i32*
  store i32 %members, i32* %0, align 4, !tbaa !30
  %data2 = getelementptr inbounds i8, i8* %call, i32 8
  %cmp.not = icmp eq i8* %initial, inttoptr (i32 -1 to i8*)
  br i1 %cmp.not, label %while.cond4.preheader, label %while.cond.preheader

while.cond.preheader:                             ; preds = %entry
  %1 = icmp eq i32 %mul, 0
  br i1 %1, label %if.end, label %while.body.preheader

while.body.preheader:                             ; preds = %while.cond.preheader
  %2 = add i32 %mul, -1
  %xtraiter = and i32 %mul, 7
  %lcmp.mod.not = icmp eq i32 %xtraiter, 0
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol.preheader

while.body.prol.preheader:                        ; preds = %while.body.preheader
  br label %while.body.prol

while.body.prol:                                  ; preds = %while.body.prol.preheader, %while.body.prol
  %data.026.prol = phi i8* [ %incdec.ptr3.prol, %while.body.prol ], [ %data2, %while.body.prol.preheader ]
  %size_array.025.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %mul, %while.body.prol.preheader ]
  %initial.addr.024.prol = phi i8* [ %incdec.ptr.prol, %while.body.prol ], [ %initial, %while.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.prol.preheader ]
  %dec.prol = add i32 %size_array.025.prol, -1
  %incdec.ptr.prol = getelementptr inbounds i8, i8* %initial.addr.024.prol, i32 1
  %3 = load i8, i8* %initial.addr.024.prol, align 1, !tbaa !12
  %incdec.ptr3.prol = getelementptr inbounds i8, i8* %data.026.prol, i32 1
  store i8 %3, i8* %data.026.prol, align 1, !tbaa !12
  %prol.iter.sub = add i32 %prol.iter, -1
  %prol.iter.cmp.not = icmp eq i32 %prol.iter.sub, 0
  br i1 %prol.iter.cmp.not, label %while.body.prol.loopexit, label %while.body.prol, !llvm.loop !32

while.body.prol.loopexit:                         ; preds = %while.body.prol, %while.body.preheader
  %data.026.unr = phi i8* [ %data2, %while.body.preheader ], [ %incdec.ptr3.prol, %while.body.prol ]
  %size_array.025.unr = phi i32 [ %mul, %while.body.preheader ], [ %dec.prol, %while.body.prol ]
  %initial.addr.024.unr = phi i8* [ %initial, %while.body.preheader ], [ %incdec.ptr.prol, %while.body.prol ]
  %4 = icmp ult i32 %2, 7
  br i1 %4, label %if.end, label %while.body.preheader2

while.body.preheader2:                            ; preds = %while.body.prol.loopexit
  br label %while.body

while.cond4.preheader:                            ; preds = %entry
  %5 = icmp eq i32 %mul, 0
  br i1 %5, label %if.end, label %while.body7.preheader

while.body7.preheader:                            ; preds = %while.cond4.preheader
  %6 = add i32 %mul, -1
  %xtraiter34 = and i32 %mul, 7
  %lcmp.mod35.not = icmp eq i32 %xtraiter34, 0
  br i1 %lcmp.mod35.not, label %while.body7.prol.loopexit, label %while.body7.prol.preheader

while.body7.prol.preheader:                       ; preds = %while.body7.preheader
  br label %while.body7.prol

while.body7.prol:                                 ; preds = %while.body7.prol.preheader, %while.body7.prol
  %data.129.prol = phi i8* [ %incdec.ptr8.prol, %while.body7.prol ], [ %data2, %while.body7.prol.preheader ]
  %size_array.128.prol = phi i32 [ %dec5.prol, %while.body7.prol ], [ %mul, %while.body7.prol.preheader ]
  %prol.iter36 = phi i32 [ %prol.iter36.sub, %while.body7.prol ], [ %xtraiter34, %while.body7.prol.preheader ]
  %dec5.prol = add i32 %size_array.128.prol, -1
  %incdec.ptr8.prol = getelementptr inbounds i8, i8* %data.129.prol, i32 1
  store i8 0, i8* %data.129.prol, align 1, !tbaa !12
  %prol.iter36.sub = add i32 %prol.iter36, -1
  %prol.iter36.cmp.not = icmp eq i32 %prol.iter36.sub, 0
  br i1 %prol.iter36.cmp.not, label %while.body7.prol.loopexit, label %while.body7.prol, !llvm.loop !33

while.body7.prol.loopexit:                        ; preds = %while.body7.prol, %while.body7.preheader
  %data.129.unr = phi i8* [ %data2, %while.body7.preheader ], [ %incdec.ptr8.prol, %while.body7.prol ]
  %size_array.128.unr = phi i32 [ %mul, %while.body7.preheader ], [ %dec5.prol, %while.body7.prol ]
  %7 = icmp ult i32 %6, 7
  br i1 %7, label %if.end, label %while.body7.preheader1

while.body7.preheader1:                           ; preds = %while.body7.prol.loopexit
  br label %while.body7

while.body:                                       ; preds = %while.body.preheader2, %while.body
  %data.026 = phi i8* [ %scevgep26, %while.body ], [ %data.026.unr, %while.body.preheader2 ]
  %size_array.025 = phi i32 [ %dec.7, %while.body ], [ %size_array.025.unr, %while.body.preheader2 ]
  %initial.addr.024 = phi i8* [ %scevgep18, %while.body ], [ %initial.addr.024.unr, %while.body.preheader2 ]
  %8 = load i8, i8* %initial.addr.024, align 1, !tbaa !12
  store i8 %8, i8* %data.026, align 1, !tbaa !12
  %scevgep11 = getelementptr i8, i8* %initial.addr.024, i32 1
  %9 = load i8, i8* %scevgep11, align 1, !tbaa !12
  %scevgep19 = getelementptr i8, i8* %data.026, i32 1
  store i8 %9, i8* %scevgep19, align 1, !tbaa !12
  %scevgep12 = getelementptr i8, i8* %initial.addr.024, i32 2
  %10 = load i8, i8* %scevgep12, align 1, !tbaa !12
  %scevgep20 = getelementptr i8, i8* %data.026, i32 2
  store i8 %10, i8* %scevgep20, align 1, !tbaa !12
  %scevgep13 = getelementptr i8, i8* %initial.addr.024, i32 3
  %11 = load i8, i8* %scevgep13, align 1, !tbaa !12
  %scevgep21 = getelementptr i8, i8* %data.026, i32 3
  store i8 %11, i8* %scevgep21, align 1, !tbaa !12
  %scevgep14 = getelementptr i8, i8* %initial.addr.024, i32 4
  %12 = load i8, i8* %scevgep14, align 1, !tbaa !12
  %scevgep22 = getelementptr i8, i8* %data.026, i32 4
  store i8 %12, i8* %scevgep22, align 1, !tbaa !12
  %scevgep15 = getelementptr i8, i8* %initial.addr.024, i32 5
  %13 = load i8, i8* %scevgep15, align 1, !tbaa !12
  %scevgep23 = getelementptr i8, i8* %data.026, i32 5
  store i8 %13, i8* %scevgep23, align 1, !tbaa !12
  %scevgep16 = getelementptr i8, i8* %initial.addr.024, i32 6
  %14 = load i8, i8* %scevgep16, align 1, !tbaa !12
  %scevgep24 = getelementptr i8, i8* %data.026, i32 6
  store i8 %14, i8* %scevgep24, align 1, !tbaa !12
  %dec.7 = add i32 %size_array.025, -8
  %scevgep17 = getelementptr i8, i8* %initial.addr.024, i32 7
  %15 = load i8, i8* %scevgep17, align 1, !tbaa !12
  %scevgep25 = getelementptr i8, i8* %data.026, i32 7
  store i8 %15, i8* %scevgep25, align 1, !tbaa !12
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep18 = getelementptr i8, i8* %initial.addr.024, i32 8
  %scevgep26 = getelementptr i8, i8* %data.026, i32 8
  br i1 %tobool.not.7, label %if.end, label %while.body, !llvm.loop !34

while.body7:                                      ; preds = %while.body7.preheader1, %while.body7
  %data.129 = phi i8* [ %scevgep10, %while.body7 ], [ %data.129.unr, %while.body7.preheader1 ]
  %size_array.128 = phi i32 [ %dec5.7, %while.body7 ], [ %size_array.128.unr, %while.body7.preheader1 ]
  store i8 0, i8* %data.129, align 1, !tbaa !12
  %scevgep = getelementptr i8, i8* %data.129, i32 1
  store i8 0, i8* %scevgep, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %data.129, i32 2
  store i8 0, i8* %scevgep4, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %data.129, i32 3
  store i8 0, i8* %scevgep5, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %data.129, i32 4
  store i8 0, i8* %scevgep6, align 1, !tbaa !12
  %scevgep7 = getelementptr i8, i8* %data.129, i32 5
  store i8 0, i8* %scevgep7, align 1, !tbaa !12
  %scevgep8 = getelementptr i8, i8* %data.129, i32 6
  store i8 0, i8* %scevgep8, align 1, !tbaa !12
  %dec5.7 = add i32 %size_array.128, -8
  %scevgep9 = getelementptr i8, i8* %data.129, i32 7
  store i8 0, i8* %scevgep9, align 1, !tbaa !12
  %tobool6.not.7 = icmp eq i32 %dec5.7, 0
  %scevgep10 = getelementptr i8, i8* %data.129, i32 8
  br i1 %tobool6.not.7, label %if.end, label %while.body7, !llvm.loop !35

if.end:                                           ; preds = %while.body, %while.body7, %while.body.prol.loopexit, %while.body7.prol.loopexit, %while.cond.preheader, %while.cond4.preheader
  %16 = bitcast i8* %call to %struct.vector*
  ret %struct.vector* %16
}

; Function Attrs: noinline nounwind
define hidden nonnull i8* @__malloc(i32 %size) local_unnamed_addr #4 {
entry:
  br label %land.rhs

land.rhs:                                         ; preds = %while.body, %entry
  %cur.012 = phi %struct.chunk* [ inttoptr (i32 65536 to %struct.chunk*), %entry ], [ %2, %while.body ]
  %allocated = getelementptr inbounds %struct.chunk, %struct.chunk* %cur.012, i32 0, i32 3
  %0 = load i32, i32* %allocated, align 4, !tbaa !36
  %tobool1.not = icmp eq i32 %0, 0
  br i1 %tobool1.not, label %lor.rhs, label %while.body

lor.rhs:                                          ; preds = %land.rhs
  %length = getelementptr inbounds %struct.chunk, %struct.chunk* %cur.012, i32 0, i32 2
  %1 = load i32, i32* %length, align 4, !tbaa !40
  %cmp = icmp ult i32 %1, %size
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %land.rhs, %lor.rhs
  %next1 = bitcast %struct.chunk* %cur.012 to %struct.chunk**
  %2 = load %struct.chunk*, %struct.chunk** %next1, align 4, !tbaa !41
  %tobool.not = icmp eq %struct.chunk* %2, null
  br i1 %tobool.not, label %while.body.while.end_crit_edge, label %land.rhs

while.body.while.end_crit_edge:                   ; preds = %while.body
  %.pre = load i32, i32* inttoptr (i32 8 to i32*), align 8, !tbaa !40
  br label %while.end

while.end:                                        ; preds = %lor.rhs, %while.body.while.end_crit_edge
  %3 = phi i32 [ %.pre, %while.body.while.end_crit_edge ], [ %1, %lor.rhs ]
  %cur.0.lcssa = phi %struct.chunk* [ null, %while.body.while.end_crit_edge ], [ %cur.012, %lor.rhs ]
  %add.i = add i32 %size, 7
  %and.i = and i32 %add.i, -8
  %sub.i = sub i32 %3, %and.i
  %cmp.i = icmp ugt i32 %sub.i, 23
  br i1 %cmp.i, label %if.then.i, label %shrink_chunk.exit

if.then.i:                                        ; preds = %while.end
  %add.ptr.i = getelementptr inbounds %struct.chunk, %struct.chunk* %cur.0.lcssa, i32 1
  %4 = bitcast %struct.chunk* %add.ptr.i to i8*
  %add.ptr1.i = getelementptr i8, i8* %4, i32 %and.i
  %next.i2 = bitcast %struct.chunk* %cur.0.lcssa to %struct.chunk**
  %5 = load %struct.chunk*, %struct.chunk** %next.i2, align 4, !tbaa !41
  %next2.i = bitcast i8* %add.ptr1.i to %struct.chunk**
  store %struct.chunk* %5, %struct.chunk** %next2.i, align 4, !tbaa !41
  %cmp3.not.i = icmp eq %struct.chunk* %5, null
  br i1 %cmp3.not.i, label %if.end.i, label %if.then4.i

if.then4.i:                                       ; preds = %if.then.i
  %prev.i = getelementptr inbounds %struct.chunk, %struct.chunk* %5, i32 0, i32 1
  %6 = bitcast %struct.chunk** %prev.i to i8**
  store i8* %add.ptr1.i, i8** %6, align 4, !tbaa !42
  br label %if.end.i

if.end.i:                                         ; preds = %if.then4.i, %if.then.i
  %7 = bitcast %struct.chunk* %cur.0.lcssa to i8**
  store i8* %add.ptr1.i, i8** %7, align 4, !tbaa !41
  %prev7.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 4
  %8 = bitcast i8* %prev7.i to %struct.chunk**
  store %struct.chunk* %cur.0.lcssa, %struct.chunk** %8, align 4, !tbaa !42
  %allocated.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 12
  %9 = bitcast i8* %allocated.i to i32*
  store i32 0, i32* %9, align 4, !tbaa !36
  %sub10.i = add i32 %sub.i, -16
  %length11.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 8
  %10 = bitcast i8* %length11.i to i32*
  store i32 %sub10.i, i32* %10, align 4, !tbaa !40
  %11 = bitcast %struct.chunk* %cur.0.lcssa to i8*
  %sunkaddr = getelementptr inbounds i8, i8* %11, i32 8
  %12 = bitcast i8* %sunkaddr to i32*
  store i32 %and.i, i32* %12, align 4, !tbaa !40
  br label %shrink_chunk.exit

shrink_chunk.exit:                                ; preds = %while.end, %if.end.i
  %allocated3 = getelementptr inbounds %struct.chunk, %struct.chunk* %cur.0.lcssa, i32 0, i32 3
  store i32 1, i32* %allocated3, align 4, !tbaa !36
  %incdec.ptr = getelementptr inbounds %struct.chunk, %struct.chunk* %cur.0.lcssa, i32 1
  %13 = bitcast %struct.chunk* %incdec.ptr to i8*
  ret i8* %13
}

; Function Attrs: inaccessiblememonly nofree nosync nounwind willreturn
declare void @llvm.assume(i1 noundef) #5

; Function Attrs: nofree norecurse nosync nounwind readonly
define hidden i64 @vector_hash(%struct.vector* nocapture readonly %v) local_unnamed_addr #2 {
entry:
  %len21 = bitcast %struct.vector* %v to i32*
  %0 = load i32, i32* %len21, align 4, !tbaa !30
  %tobool.not8 = icmp eq i32 %0, 0
  br i1 %tobool.not8, label %while.end, label %while.body.lr.ph

while.body.lr.ph:                                 ; preds = %entry
  %arraydecay = getelementptr inbounds %struct.vector, %struct.vector* %v, i32 0, i32 2, i32 0
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
  br i1 %cmp.not, label %while.cond.preheader, label %return

while.cond.preheader:                             ; preds = %entry
  br label %while.cond

while.cond:                                       ; preds = %while.cond.preheader, %while.body
  %left.addr.0 = phi i8* [ %incdec.ptr, %while.body ], [ %left, %while.cond.preheader ]
  %left_len.addr.0 = phi i32 [ %dec, %while.body ], [ %left_len, %while.cond.preheader ]
  %right.addr.0 = phi i8* [ %incdec.ptr1, %while.body ], [ %right, %while.cond.preheader ]
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
define hidden %struct.vector* @concat(i8* nocapture readonly %left, i32 %left_len, i8* nocapture readonly %right, i32 %right_len) local_unnamed_addr #3 {
entry:
  %add = add i32 %right_len, %left_len
  %add1 = add i32 %add, 8
  %call = tail call i8* @__malloc(i32 %add1) #18
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
  br i1 %lcmp.mod.not, label %while.body.prol.loopexit, label %while.body.prol.preheader

while.body.prol.preheader:                        ; preds = %while.body.preheader
  br label %while.body.prol

while.body.prol:                                  ; preds = %while.body.prol.preheader, %while.body.prol
  %data.025.prol = phi i8* [ %incdec.ptr3.prol, %while.body.prol ], [ %data2, %while.body.prol.preheader ]
  %left.addr.024.prol = phi i8* [ %incdec.ptr.prol, %while.body.prol ], [ %left, %while.body.prol.preheader ]
  %left_len.addr.023.prol = phi i32 [ %dec.prol, %while.body.prol ], [ %left_len, %while.body.prol.preheader ]
  %prol.iter = phi i32 [ %prol.iter.sub, %while.body.prol ], [ %xtraiter, %while.body.prol.preheader ]
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
  br i1 %3, label %while.cond4.preheader, label %while.body.preheader2

while.body.preheader2:                            ; preds = %while.body.prol.loopexit
  br label %while.body

while.cond4.preheader:                            ; preds = %while.body, %while.body.prol.loopexit, %entry
  %data.0.lcssa = phi i8* [ %data2, %entry ], [ %incdec.ptr3.lcssa.unr, %while.body.prol.loopexit ], [ %incdec.ptr3.7, %while.body ]
  %tobool6.not26 = icmp eq i32 %right_len, 0
  br i1 %tobool6.not26, label %while.end10, label %while.body7.preheader

while.body7.preheader:                            ; preds = %while.cond4.preheader
  %4 = add i32 %right_len, -1
  %xtraiter30 = and i32 %right_len, 7
  %lcmp.mod31.not = icmp eq i32 %xtraiter30, 0
  br i1 %lcmp.mod31.not, label %while.body7.prol.loopexit, label %while.body7.prol.preheader

while.body7.prol.preheader:                       ; preds = %while.body7.preheader
  br label %while.body7.prol

while.body7.prol:                                 ; preds = %while.body7.prol.preheader, %while.body7.prol
  %data.129.prol = phi i8* [ %incdec.ptr9.prol, %while.body7.prol ], [ %data.0.lcssa, %while.body7.prol.preheader ]
  %right_len.addr.028.prol = phi i32 [ %dec5.prol, %while.body7.prol ], [ %right_len, %while.body7.prol.preheader ]
  %right.addr.027.prol = phi i8* [ %incdec.ptr8.prol, %while.body7.prol ], [ %right, %while.body7.prol.preheader ]
  %prol.iter32 = phi i32 [ %prol.iter32.sub, %while.body7.prol ], [ %xtraiter30, %while.body7.prol.preheader ]
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
  br i1 %6, label %while.end10, label %while.body7.preheader1

while.body7.preheader1:                           ; preds = %while.body7.prol.loopexit
  br label %while.body7

while.body:                                       ; preds = %while.body.preheader2, %while.body
  %data.025 = phi i8* [ %scevgep33, %while.body ], [ %data.025.unr, %while.body.preheader2 ]
  %left.addr.024 = phi i8* [ %scevgep25, %while.body ], [ %left.addr.024.unr, %while.body.preheader2 ]
  %left_len.addr.023 = phi i32 [ %dec.7, %while.body ], [ %left_len.addr.023.unr, %while.body.preheader2 ]
  %7 = load i8, i8* %left.addr.024, align 1, !tbaa !12
  store i8 %7, i8* %data.025, align 1, !tbaa !12
  %scevgep18 = getelementptr i8, i8* %left.addr.024, i32 1
  %8 = load i8, i8* %scevgep18, align 1, !tbaa !12
  %scevgep26 = getelementptr i8, i8* %data.025, i32 1
  store i8 %8, i8* %scevgep26, align 1, !tbaa !12
  %scevgep19 = getelementptr i8, i8* %left.addr.024, i32 2
  %9 = load i8, i8* %scevgep19, align 1, !tbaa !12
  %scevgep27 = getelementptr i8, i8* %data.025, i32 2
  store i8 %9, i8* %scevgep27, align 1, !tbaa !12
  %scevgep20 = getelementptr i8, i8* %left.addr.024, i32 3
  %10 = load i8, i8* %scevgep20, align 1, !tbaa !12
  %scevgep28 = getelementptr i8, i8* %data.025, i32 3
  store i8 %10, i8* %scevgep28, align 1, !tbaa !12
  %scevgep21 = getelementptr i8, i8* %left.addr.024, i32 4
  %11 = load i8, i8* %scevgep21, align 1, !tbaa !12
  %scevgep29 = getelementptr i8, i8* %data.025, i32 4
  store i8 %11, i8* %scevgep29, align 1, !tbaa !12
  %scevgep22 = getelementptr i8, i8* %left.addr.024, i32 5
  %12 = load i8, i8* %scevgep22, align 1, !tbaa !12
  %scevgep30 = getelementptr i8, i8* %data.025, i32 5
  store i8 %12, i8* %scevgep30, align 1, !tbaa !12
  %scevgep23 = getelementptr i8, i8* %left.addr.024, i32 6
  %13 = load i8, i8* %scevgep23, align 1, !tbaa !12
  %scevgep31 = getelementptr i8, i8* %data.025, i32 6
  store i8 %13, i8* %scevgep31, align 1, !tbaa !12
  %dec.7 = add i32 %left_len.addr.023, -8
  %scevgep24 = getelementptr i8, i8* %left.addr.024, i32 7
  %14 = load i8, i8* %scevgep24, align 1, !tbaa !12
  %incdec.ptr3.7 = getelementptr inbounds i8, i8* %data.025, i32 8
  %scevgep32 = getelementptr i8, i8* %data.025, i32 7
  store i8 %14, i8* %scevgep32, align 1, !tbaa !12
  %tobool.not.7 = icmp eq i32 %dec.7, 0
  %scevgep25 = getelementptr i8, i8* %left.addr.024, i32 8
  %scevgep33 = getelementptr i8, i8* %data.025, i32 8
  br i1 %tobool.not.7, label %while.cond4.preheader, label %while.body, !llvm.loop !46

while.body7:                                      ; preds = %while.body7.preheader1, %while.body7
  %data.129 = phi i8* [ %scevgep17, %while.body7 ], [ %data.129.unr, %while.body7.preheader1 ]
  %right_len.addr.028 = phi i32 [ %dec5.7, %while.body7 ], [ %right_len.addr.028.unr, %while.body7.preheader1 ]
  %right.addr.027 = phi i8* [ %scevgep9, %while.body7 ], [ %right.addr.027.unr, %while.body7.preheader1 ]
  %15 = load i8, i8* %right.addr.027, align 1, !tbaa !12
  store i8 %15, i8* %data.129, align 1, !tbaa !12
  %scevgep = getelementptr i8, i8* %right.addr.027, i32 1
  %16 = load i8, i8* %scevgep, align 1, !tbaa !12
  %scevgep10 = getelementptr i8, i8* %data.129, i32 1
  store i8 %16, i8* %scevgep10, align 1, !tbaa !12
  %scevgep3 = getelementptr i8, i8* %right.addr.027, i32 2
  %17 = load i8, i8* %scevgep3, align 1, !tbaa !12
  %scevgep11 = getelementptr i8, i8* %data.129, i32 2
  store i8 %17, i8* %scevgep11, align 1, !tbaa !12
  %scevgep4 = getelementptr i8, i8* %right.addr.027, i32 3
  %18 = load i8, i8* %scevgep4, align 1, !tbaa !12
  %scevgep12 = getelementptr i8, i8* %data.129, i32 3
  store i8 %18, i8* %scevgep12, align 1, !tbaa !12
  %scevgep5 = getelementptr i8, i8* %right.addr.027, i32 4
  %19 = load i8, i8* %scevgep5, align 1, !tbaa !12
  %scevgep13 = getelementptr i8, i8* %data.129, i32 4
  store i8 %19, i8* %scevgep13, align 1, !tbaa !12
  %scevgep6 = getelementptr i8, i8* %right.addr.027, i32 5
  %20 = load i8, i8* %scevgep6, align 1, !tbaa !12
  %scevgep14 = getelementptr i8, i8* %data.129, i32 5
  store i8 %20, i8* %scevgep14, align 1, !tbaa !12
  %scevgep7 = getelementptr i8, i8* %right.addr.027, i32 6
  %21 = load i8, i8* %scevgep7, align 1, !tbaa !12
  %scevgep15 = getelementptr i8, i8* %data.129, i32 6
  store i8 %21, i8* %scevgep15, align 1, !tbaa !12
  %dec5.7 = add i32 %right_len.addr.028, -8
  %scevgep8 = getelementptr i8, i8* %right.addr.027, i32 7
  %22 = load i8, i8* %scevgep8, align 1, !tbaa !12
  %scevgep16 = getelementptr i8, i8* %data.129, i32 7
  store i8 %22, i8* %scevgep16, align 1, !tbaa !12
  %tobool6.not.7 = icmp eq i32 %dec5.7, 0
  %scevgep9 = getelementptr i8, i8* %right.addr.027, i32 8
  %scevgep17 = getelementptr i8, i8* %data.129, i32 8
  br i1 %tobool6.not.7, label %while.end10, label %while.body7, !llvm.loop !47

while.end10:                                      ; preds = %while.body7, %while.body7.prol.loopexit, %while.cond4.preheader
  %23 = bitcast i8* %call to %struct.vector*
  ret %struct.vector* %23
}

; Function Attrs: nofree nounwind
define hidden void @__init_heap() local_unnamed_addr #6 {
entry:
  store %struct.chunk* null, %struct.chunk** inttoptr (i32 65540 to %struct.chunk**), align 4, !tbaa !42
  store %struct.chunk* null, %struct.chunk** inttoptr (i32 65536 to %struct.chunk**), align 65536, !tbaa !41
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
  %next1 = bitcast i8* %incdec.ptr to %struct.chunk**
  %1 = load %struct.chunk*, %struct.chunk** %next1, align 4, !tbaa !41
  %tobool2.not = icmp eq %struct.chunk* %1, null
  br i1 %tobool2.not, label %if.end13, label %land.lhs.true

land.lhs.true:                                    ; preds = %if.then
  %allocated3 = getelementptr inbounds %struct.chunk, %struct.chunk* %1, i32 0, i32 3
  %2 = load i32, i32* %allocated3, align 4, !tbaa !36
  %tobool4.not = icmp eq i32 %2, 0
  br i1 %tobool4.not, label %if.then5, label %if.end13

if.then5:                                         ; preds = %land.lhs.true
  %3 = bitcast i8* %incdec.ptr to %struct.chunk**
  %next61 = bitcast %struct.chunk* %1 to %struct.chunk**
  %4 = load %struct.chunk*, %struct.chunk** %next61, align 4, !tbaa !41
  store %struct.chunk* %4, %struct.chunk** %3, align 4, !tbaa !41
  %cmp.not = icmp eq %struct.chunk* %4, null
  br i1 %cmp.not, label %if.end, label %if.then8

if.then8:                                         ; preds = %if.then5
  %prev = getelementptr inbounds %struct.chunk, %struct.chunk* %4, i32 0, i32 1
  %5 = bitcast %struct.chunk** %prev to i8**
  store i8* %incdec.ptr, i8** %5, align 4, !tbaa !42
  br label %if.end

if.end:                                           ; preds = %if.then5, %if.then8
  %length = getelementptr inbounds %struct.chunk, %struct.chunk* %1, i32 0, i32 2
  %6 = load i32, i32* %length, align 4, !tbaa !40
  %add = add i32 %6, 16
  %length10 = getelementptr inbounds i8, i8* %m, i32 -8
  %7 = bitcast i8* %length10 to i32*
  %8 = load i32, i32* %7, align 4, !tbaa !40
  %add11 = add i32 %add, %8
  store i32 %add11, i32* %7, align 4, !tbaa !40
  br label %if.end13

if.end13:                                         ; preds = %land.lhs.true, %if.then, %if.end
  %next.0 = phi %struct.chunk* [ %1, %land.lhs.true ], [ %4, %if.end ], [ null, %if.then ]
  %prev15 = getelementptr inbounds i8, i8* %m, i32 -12
  %9 = bitcast i8* %prev15 to %struct.chunk**
  %10 = load %struct.chunk*, %struct.chunk** %9, align 4, !tbaa !42
  %tobool16.not = icmp eq %struct.chunk* %10, null
  br i1 %tobool16.not, label %if.end28, label %land.lhs.true17

land.lhs.true17:                                  ; preds = %if.end13
  %allocated18 = getelementptr inbounds %struct.chunk, %struct.chunk* %10, i32 0, i32 3
  %11 = load i32, i32* %allocated18, align 4, !tbaa !36
  %tobool19.not = icmp eq i32 %11, 0
  br i1 %tobool19.not, label %if.then20, label %if.end28

if.then20:                                        ; preds = %land.lhs.true17
  %next212 = bitcast %struct.chunk* %10 to %struct.chunk**
  store %struct.chunk* %next.0, %struct.chunk** %next212, align 4, !tbaa !41
  %prev22 = getelementptr inbounds %struct.chunk, %struct.chunk* %next.0, i32 0, i32 1
  store %struct.chunk* %10, %struct.chunk** %prev22, align 4, !tbaa !42
  %length23 = getelementptr inbounds i8, i8* %m, i32 -8
  %12 = bitcast i8* %length23 to i32*
  %13 = load i32, i32* %12, align 4, !tbaa !40
  %add24 = add i32 %13, 16
  %length25 = getelementptr inbounds %struct.chunk, %struct.chunk* %10, i32 0, i32 2
  %14 = load i32, i32* %length25, align 4, !tbaa !40
  %add26 = add i32 %add24, %14
  store i32 %add26, i32* %length25, align 4, !tbaa !40
  br label %if.end28

if.end28:                                         ; preds = %if.then20, %if.end13, %land.lhs.true17, %entry
  ret void
}

; Function Attrs: nounwind
define hidden i8* @__realloc(i8* %m, i32 %size) local_unnamed_addr #9 {
entry:
  %incdec.ptr = getelementptr inbounds i8, i8* %m, i32 -16
  %next1 = bitcast i8* %incdec.ptr to %struct.chunk**
  %0 = load %struct.chunk*, %struct.chunk** %next1, align 4, !tbaa !41
  %tobool.not = icmp eq %struct.chunk* %0, null
  br i1 %tobool.not, label %if.else, label %land.lhs.true

land.lhs.true:                                    ; preds = %entry
  %allocated = getelementptr inbounds %struct.chunk, %struct.chunk* %0, i32 0, i32 3
  %1 = load i32, i32* %allocated, align 4, !tbaa !36
  %tobool2.not = icmp eq i32 %1, 0
  br i1 %tobool2.not, label %land.lhs.true3, label %if.else

land.lhs.true3:                                   ; preds = %land.lhs.true
  %length = getelementptr inbounds i8, i8* %m, i32 -8
  %2 = bitcast i8* %length to i32*
  %3 = load i32, i32* %2, align 4, !tbaa !40
  %length4 = getelementptr inbounds %struct.chunk, %struct.chunk* %0, i32 0, i32 2
  %4 = load i32, i32* %length4, align 4, !tbaa !40
  %add = add i32 %3, 16
  %add5 = add i32 %add, %4
  %cmp.not = icmp ult i32 %add5, %size
  br i1 %cmp.not, label %if.else, label %if.then

if.then:                                          ; preds = %land.lhs.true3
  %5 = bitcast i8* %length to i32*
  %6 = bitcast i8* %incdec.ptr to %struct.chunk**
  %next616 = bitcast %struct.chunk* %0 to %struct.chunk**
  %7 = load %struct.chunk*, %struct.chunk** %next616, align 4, !tbaa !41
  store %struct.chunk* %7, %struct.chunk** %6, align 4, !tbaa !41
  %prev = getelementptr inbounds %struct.chunk, %struct.chunk* %7, i32 0, i32 1
  %8 = bitcast %struct.chunk** %prev to i8**
  store i8* %incdec.ptr, i8** %8, align 4, !tbaa !42
  store i32 %add5, i32* %5, align 4, !tbaa !40
  %add.i = add i32 %size, 7
  %and.i = and i32 %add.i, -8
  %sub.i = sub i32 %add5, %and.i
  %cmp.i = icmp ugt i32 %sub.i, 23
  br i1 %cmp.i, label %if.then.i, label %cleanup

if.then.i:                                        ; preds = %if.then
  %add.ptr1.i = getelementptr i8, i8* %m, i32 %and.i
  %next2.i = bitcast i8* %add.ptr1.i to %struct.chunk**
  store %struct.chunk* %7, %struct.chunk** %next2.i, align 4, !tbaa !41
  %cmp3.not.i = icmp eq %struct.chunk* %7, null
  br i1 %cmp3.not.i, label %if.end.i, label %if.then4.i

if.then4.i:                                       ; preds = %if.then.i
  %9 = bitcast %struct.chunk* %7 to i8*
  %sunkaddr = getelementptr inbounds i8, i8* %9, i32 4
  %10 = bitcast i8* %sunkaddr to i8**
  store i8* %add.ptr1.i, i8** %10, align 4, !tbaa !42
  br label %if.end.i

if.end.i:                                         ; preds = %if.then4.i, %if.then.i
  %11 = bitcast i8* %length to i32*
  %12 = bitcast i8* %incdec.ptr to i8**
  store i8* %add.ptr1.i, i8** %12, align 4, !tbaa !41
  %prev7.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 4
  %13 = bitcast i8* %prev7.i to i8**
  store i8* %incdec.ptr, i8** %13, align 4, !tbaa !42
  %allocated.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 12
  %14 = bitcast i8* %allocated.i to i32*
  store i32 0, i32* %14, align 4, !tbaa !36
  %sub10.i = add i32 %sub.i, -16
  %length11.i = getelementptr inbounds i8, i8* %add.ptr1.i, i32 8
  %15 = bitcast i8* %length11.i to i32*
  store i32 %sub10.i, i32* %15, align 4, !tbaa !40
  store i32 %and.i, i32* %11, align 4, !tbaa !40
  br label %cleanup

if.else:                                          ; preds = %land.lhs.true3, %land.lhs.true, %entry
  %call = tail call i8* @__malloc(i32 %size) #19
  %div = lshr i32 %size, 3
  %16 = bitcast i8* %call to i64*
  %17 = bitcast i8* %m to i64*
  %18 = add i32 %div, -1
  %xtraiter.i = and i32 %div, 7
  %lcmp.mod.not.i = icmp eq i32 %xtraiter.i, 0
  br i1 %lcmp.mod.not.i, label %do.body.prol.loopexit.i, label %do.body.prol.i.preheader

do.body.prol.i.preheader:                         ; preds = %if.else
  %19 = bitcast i8* %m to i64*
  %20 = bitcast i8* %call to i64*
  br label %do.body.prol.i

do.body.prol.i:                                   ; preds = %do.body.prol.i.preheader, %do.body.prol.i
  %length.addr.0.prol.i = phi i32 [ %dec.prol.i, %do.body.prol.i ], [ %div, %do.body.prol.i.preheader ]
  %dest.0.prol.i = phi i64* [ %incdec.ptr1.prol.i, %do.body.prol.i ], [ %20, %do.body.prol.i.preheader ]
  %src.0.prol.i = phi i64* [ %incdec.ptr.prol.i, %do.body.prol.i ], [ %19, %do.body.prol.i.preheader ]
  %prol.iter.i = phi i32 [ %prol.iter.sub.i, %do.body.prol.i ], [ %xtraiter.i, %do.body.prol.i.preheader ]
  %incdec.ptr.prol.i = getelementptr inbounds i64, i64* %src.0.prol.i, i32 1
  %21 = load i64, i64* %src.0.prol.i, align 8, !tbaa !4
  %incdec.ptr1.prol.i = getelementptr inbounds i64, i64* %dest.0.prol.i, i32 1
  store i64 %21, i64* %dest.0.prol.i, align 8, !tbaa !4
  %dec.prol.i = add i32 %length.addr.0.prol.i, -1
  %prol.iter.sub.i = add i32 %prol.iter.i, -1
  %prol.iter.cmp.not.i = icmp eq i32 %prol.iter.sub.i, 0
  br i1 %prol.iter.cmp.not.i, label %do.body.prol.loopexit.i, label %do.body.prol.i, !llvm.loop !15

do.body.prol.loopexit.i:                          ; preds = %do.body.prol.i, %if.else
  %length.addr.0.unr.i = phi i32 [ %div, %if.else ], [ %dec.prol.i, %do.body.prol.i ]
  %dest.0.unr.i = phi i64* [ %16, %if.else ], [ %incdec.ptr1.prol.i, %do.body.prol.i ]
  %src.0.unr.i = phi i64* [ %17, %if.else ], [ %incdec.ptr.prol.i, %do.body.prol.i ]
  %22 = icmp ult i32 %18, 7
  br i1 %22, label %__memcpy8.exit, label %do.body.i.preheader

do.body.i.preheader:                              ; preds = %do.body.prol.loopexit.i
  br label %do.body.i

do.body.i:                                        ; preds = %do.body.i.preheader, %do.body.i
  %length.addr.0.i = phi i32 [ %dec.7.i, %do.body.i ], [ %length.addr.0.unr.i, %do.body.i.preheader ]
  %dest.0.i = phi i64* [ %scevgep15, %do.body.i ], [ %dest.0.unr.i, %do.body.i.preheader ]
  %src.0.i = phi i64* [ %scevgep7, %do.body.i ], [ %src.0.unr.i, %do.body.i.preheader ]
  %23 = load i64, i64* %src.0.i, align 8, !tbaa !4
  store i64 %23, i64* %dest.0.i, align 8, !tbaa !4
  %scevgep = getelementptr i64, i64* %src.0.i, i32 1
  %24 = load i64, i64* %scevgep, align 8, !tbaa !4
  %scevgep8 = getelementptr i64, i64* %dest.0.i, i32 1
  store i64 %24, i64* %scevgep8, align 8, !tbaa !4
  %scevgep1 = getelementptr i64, i64* %src.0.i, i32 2
  %25 = load i64, i64* %scevgep1, align 8, !tbaa !4
  %scevgep9 = getelementptr i64, i64* %dest.0.i, i32 2
  store i64 %25, i64* %scevgep9, align 8, !tbaa !4
  %scevgep2 = getelementptr i64, i64* %src.0.i, i32 3
  %26 = load i64, i64* %scevgep2, align 8, !tbaa !4
  %scevgep10 = getelementptr i64, i64* %dest.0.i, i32 3
  store i64 %26, i64* %scevgep10, align 8, !tbaa !4
  %scevgep3 = getelementptr i64, i64* %src.0.i, i32 4
  %27 = load i64, i64* %scevgep3, align 8, !tbaa !4
  %scevgep11 = getelementptr i64, i64* %dest.0.i, i32 4
  store i64 %27, i64* %scevgep11, align 8, !tbaa !4
  %scevgep4 = getelementptr i64, i64* %src.0.i, i32 5
  %28 = load i64, i64* %scevgep4, align 8, !tbaa !4
  %scevgep12 = getelementptr i64, i64* %dest.0.i, i32 5
  store i64 %28, i64* %scevgep12, align 8, !tbaa !4
  %scevgep5 = getelementptr i64, i64* %src.0.i, i32 6
  %29 = load i64, i64* %scevgep5, align 8, !tbaa !4
  %scevgep13 = getelementptr i64, i64* %dest.0.i, i32 6
  store i64 %29, i64* %scevgep13, align 8, !tbaa !4
  %scevgep6 = getelementptr i64, i64* %src.0.i, i32 7
  %30 = load i64, i64* %scevgep6, align 8, !tbaa !4
  %scevgep14 = getelementptr i64, i64* %dest.0.i, i32 7
  store i64 %30, i64* %scevgep14, align 8, !tbaa !4
  %dec.7.i = add i32 %length.addr.0.i, -8
  %tobool.not.7.i = icmp eq i32 %dec.7.i, 0
  %scevgep7 = getelementptr i64, i64* %src.0.i, i32 8
  %scevgep15 = getelementptr i64, i64* %dest.0.i, i32 8
  br i1 %tobool.not.7.i, label %__memcpy8.exit, label %do.body.i, !llvm.loop !16

__memcpy8.exit:                                   ; preds = %do.body.i, %do.body.prol.loopexit.i
  tail call void @__free(i8* nonnull %m) #19
  br label %cleanup

cleanup:                                          ; preds = %if.end.i, %if.then, %__memcpy8.exit
  %retval.0 = phi i8* [ %call, %__memcpy8.exit ], [ %m, %if.then ], [ %m, %if.end.i ]
  ret i8* %retval.0
}

; Function Attrs: nofree nounwind
define hidden void @__mul32(i32* nocapture readonly %left, i32* nocapture readonly %right, i32* nocapture %out, i32 %len) local_unnamed_addr #6 {
entry:
  %0 = icmp slt i32 %len, 0
  %smin91 = select i1 %0, i32 %len, i32 0
  %1 = add i32 %len, -1
  %scevgep9 = getelementptr i32, i32* %left, i32 %1
  br label %while.cond

while.cond:                                       ; preds = %land.rhs, %entry
  %lsr.iv10 = phi i32* [ %scevgep11, %land.rhs ], [ %scevgep9, %entry ]
  %left_len.0 = phi i32 [ %len, %entry ], [ %sub, %land.rhs ]
  %cmp = icmp sgt i32 %left_len.0, 0
  br i1 %cmp, label %land.rhs, label %while.end

land.rhs:                                         ; preds = %while.cond
  %sub = add i32 %left_len.0, -1
  %2 = load i32, i32* %lsr.iv10, align 4, !tbaa !30
  %tobool.not = icmp eq i32 %2, 0
  %scevgep11 = getelementptr i32, i32* %lsr.iv10, i32 -1
  br i1 %tobool.not, label %while.cond, label %land.rhs.while.end_crit_edge

land.rhs.while.end_crit_edge:                     ; preds = %land.rhs
  %3 = add i32 %sub, 1
  br label %while.end

while.end:                                        ; preds = %while.cond, %land.rhs.while.end_crit_edge
  %left_len.0.lcssa = phi i32 [ %3, %land.rhs.while.end_crit_edge ], [ %smin91, %while.cond ]
  %4 = add i32 %len, -1
  %scevgep6 = getelementptr i32, i32* %right, i32 %4
  br label %while.cond1

while.cond1:                                      ; preds = %land.rhs3, %while.end
  %lsr.iv7 = phi i32* [ %scevgep8, %land.rhs3 ], [ %scevgep6, %while.end ]
  %right_len.0 = phi i32 [ %len, %while.end ], [ %sub4, %land.rhs3 ]
  %cmp2 = icmp sgt i32 %right_len.0, 0
  br i1 %cmp2, label %land.rhs3, label %while.end11

land.rhs3:                                        ; preds = %while.cond1
  %sub4 = add i32 %right_len.0, -1
  %5 = load i32, i32* %lsr.iv7, align 4, !tbaa !30
  %tobool6.not = icmp eq i32 %5, 0
  %scevgep8 = getelementptr i32, i32* %lsr.iv7, i32 -1
  br i1 %tobool6.not, label %while.cond1, label %land.rhs3.while.end11_crit_edge

land.rhs3.while.end11_crit_edge:                  ; preds = %land.rhs3
  %6 = add i32 %sub4, 1
  br label %while.end11

while.end11:                                      ; preds = %while.cond1, %land.rhs3.while.end11_crit_edge
  %right_len.0.lcssa = phi i32 [ %6, %land.rhs3.while.end11_crit_edge ], [ %smin91, %while.cond1 ]
  %cmp1285 = icmp sgt i32 %len, 0
  br i1 %cmp1285, label %for.body.preheader, label %for.cond.cleanup

for.body.preheader:                               ; preds = %while.end11
  %scevgep = getelementptr i32, i32* %right, i32 -1
  br label %for.body

for.cond.cleanup:                                 ; preds = %for.cond.cleanup25, %while.end11
  ret void

for.body:                                         ; preds = %for.body.preheader, %for.cond.cleanup25
  %val1.090 = phi i64 [ %or, %for.cond.cleanup25 ], [ 0, %for.body.preheader ]
  %l.089 = phi i32 [ %inc38, %for.cond.cleanup25 ], [ 0, %for.body.preheader ]
  %left_start.088 = phi i32 [ %left_start.1, %for.cond.cleanup25 ], [ 0, %for.body.preheader ]
  %right_end.087 = phi i32 [ %spec.select76, %for.cond.cleanup25 ], [ 0, %for.body.preheader ]
  %right_start.086 = phi i32 [ %spec.select, %for.cond.cleanup25 ], [ 0, %for.body.preheader ]
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
  br i1 %cmp24.not.not79, label %for.body26.preheader, label %for.cond.cleanup25

for.body26.preheader:                             ; preds = %for.body
  %7 = add i32 %right_end.087, %inc20
  %scevgep1 = getelementptr i32, i32* %scevgep, i32 %7
  %8 = add i32 %left_start.088, %inc16
  %scevgep3 = getelementptr i32, i32* %left, i32 %8
  br label %for.body26

for.cond.cleanup25.loopexit:                      ; preds = %for.body26
  %9 = extractvalue { i64, i1 } %12, 0
  br label %for.cond.cleanup25

for.cond.cleanup25:                               ; preds = %for.cond.cleanup25.loopexit, %for.body
  %carry.1.lcssa = phi i64 [ 0, %for.body ], [ %spec.select77, %for.cond.cleanup25.loopexit ]
  %val1.1.lcssa = phi i64 [ %val1.090, %for.body ], [ %9, %for.cond.cleanup25.loopexit ]
  %conv35 = trunc i64 %val1.1.lcssa to i32
  %arrayidx36 = getelementptr inbounds i32, i32* %out, i32 %l.089
  store i32 %conv35, i32* %arrayidx36, align 4, !tbaa !30
  %shr = lshr i64 %val1.1.lcssa, 32
  %or = or i64 %shr, %carry.1.lcssa
  %inc38 = add nuw nsw i32 %l.089, 1
  %exitcond.not = icmp eq i32 %inc38, %len
  br i1 %exitcond.not, label %for.cond.cleanup, label %for.body

for.body26:                                       ; preds = %for.body26.preheader, %for.body26
  %lsr.iv4 = phi i32* [ %scevgep3, %for.body26.preheader ], [ %scevgep5, %for.body26 ]
  %lsr.iv = phi i32* [ %scevgep1, %for.body26.preheader ], [ %scevgep2, %for.body26 ]
  %r.083.in = phi i32 [ %r.083, %for.body26 ], [ %spec.select76, %for.body26.preheader ]
  %val1.182 = phi i64 [ %14, %for.body26 ], [ %val1.090, %for.body26.preheader ]
  %carry.180 = phi i64 [ %spec.select77, %for.body26 ], [ 0, %for.body26.preheader ]
  %r.083 = add nsw i32 %r.083.in, -1
  %10 = load i32, i32* %lsr.iv4, align 4, !tbaa !30
  %conv = zext i32 %10 to i64
  %11 = load i32, i32* %lsr.iv, align 4, !tbaa !30
  %conv29 = zext i32 %11 to i64
  %mul = mul nuw i64 %conv29, %conv
  %12 = tail call { i64, i1 } @llvm.uadd.with.overflow.i64(i64 %val1.182, i64 %mul)
  %13 = extractvalue { i64, i1 } %12, 1
  %14 = extractvalue { i64, i1 } %12, 0
  %add32 = add i64 %carry.180, 4294967296
  %spec.select77 = select i1 %13, i64 %add32, i64 %carry.180
  %scevgep2 = getelementptr i32, i32* %lsr.iv, i32 -1
  %scevgep5 = getelementptr i32, i32* %lsr.iv4, i32 1
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
  %call = tail call i32 @bits128(i128 %0) #19
  %cmp1152 = icmp sgt i32 %call, -1
  br i1 %cmp1152, label %for.body.preheader, label %for.cond.cleanup

for.body.preheader:                               ; preds = %if.end10
  br label %for.body

for.cond.cleanup:                                 ; preds = %for.body, %if.end10
  %q.0.lcssa = phi i128 [ 0, %if.end10 ], [ %q.1, %for.body ]
  %r.0.lcssa = phi i128 [ 0, %if.end10 ], [ %r.2, %for.body ]
  store i128 %q.0.lcssa, i128* %quotient, align 16, !tbaa !48
  store i128 %r.0.lcssa, i128* %remainder, align 16, !tbaa !48
  br label %cleanup

for.body:                                         ; preds = %for.body.preheader, %for.body
  %lsr.iv = phi i32 [ %call, %for.body.preheader ], [ %lsr.iv.next, %for.body ]
  %r.054 = phi i128 [ %r.2, %for.body ], [ 0, %for.body.preheader ]
  %q.053 = phi i128 [ %q.1, %for.body ], [ 0, %for.body.preheader ]
  %shl = shl i128 %q.053, 1
  %shl12 = shl i128 %r.054, 1
  %sh_prom = zext i32 %lsr.iv to i128
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
  %lsr.iv.next = add nsw i32 %lsr.iv, -1
  %4 = add i32 %lsr.iv.next, 2
  %cmp11 = icmp sgt i32 %4, 1
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
  %call.i = tail call i32 @bits128(i128 %7) #18
  %cmp1152.i = icmp sgt i32 %call.i, -1
  br i1 %cmp1152.i, label %for.body.preheader.i, label %for.cond.cleanup.i

for.body.preheader.i:                             ; preds = %if.end10.i
  br label %for.body.i

for.cond.cleanup.i:                               ; preds = %for.body.i, %if.end10.i
  %q.0.lcssa.i = phi i128 [ 0, %if.end10.i ], [ %q.1.i, %for.body.i ]
  %r.0.lcssa.i = phi i128 [ 0, %if.end10.i ], [ %r.2.i, %for.body.i ]
  store i128 %q.0.lcssa.i, i128* %quotient, align 16, !tbaa !48
  store i128 %r.0.lcssa.i, i128* %remainder, align 16, !tbaa !48
  br label %if.end13

for.body.i:                                       ; preds = %for.body.i, %for.body.preheader.i
  %lsr.iv = phi i32 [ %lsr.iv.next, %for.body.i ], [ %call.i, %for.body.preheader.i ]
  %r.054.i = phi i128 [ %r.2.i, %for.body.i ], [ 0, %for.body.preheader.i ]
  %q.053.i = phi i128 [ %q.1.i, %for.body.i ], [ 0, %for.body.preheader.i ]
  %shl.i = shl i128 %q.053.i, 1
  %shl12.i = shl i128 %r.054.i, 1
  %sh_prom.i = zext i32 %lsr.iv to i128
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
  %lsr.iv.next = add nsw i32 %lsr.iv, -1
  %10 = add i32 %lsr.iv.next, 2
  %cmp11.i = icmp sgt i32 %10, 1
  br i1 %cmp11.i, label %for.body.i, label %for.cond.cleanup.i

if.end13:                                         ; preds = %if.then2.i, %if.then5.i, %if.then9.i, %for.cond.cleanup.i
  %cmp18.not.unshifted = xor i8 %4, %1
  %cmp18.not = icmp sgt i8 %cmp18.not.unshifted, -1
  br i1 %cmp18.not, label %if.end22, label %if.then20

if.then20:                                        ; preds = %if.end13
  %11 = load i128, i128* %quotient, align 16, !tbaa !48
  %sub21 = sub i128 0, %11
  store i128 %sub21, i128* %quotient, align 16, !tbaa !48
  br label %if.end22

if.end22:                                         ; preds = %if.end13, %if.then20
  %12 = icmp slt i8 %1, 0
  br i1 %12, label %if.then24, label %cleanup

if.then24:                                        ; preds = %if.end22
  %13 = load i128, i128* %remainder, align 16, !tbaa !48
  %sub25 = sub i128 0, %13
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
  %2 = bitcast i256* %value to i64*
  %arrayidx.1 = getelementptr inbounds i64, i64* %2, i32 2
  %3 = load i64, i64* %arrayidx.1, align 8, !tbaa !4
  %tobool.not.1 = icmp eq i64 %3, 0
  br i1 %tobool.not.1, label %for.inc.1, label %cleanup

cleanup:                                          ; preds = %for.inc.2, %for.inc.1, %for.inc, %entry
  %i.013.lcssa = phi i32 [ 192, %entry ], [ 128, %for.inc ], [ 64, %for.inc.1 ], [ 0, %for.inc.2 ]
  %.lcssa = phi i64 [ %1, %entry ], [ %3, %for.inc ], [ %7, %for.inc.1 ], [ %9, %for.inc.2 ]
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
  %4 = trunc i64 %v.addr.4.lobit.i to i32
  %.not.i = xor i32 %4, -1
  %spec.select48.i = add nuw nsw i32 %h.4.i, %i.013.lcssa
  %add = add i32 %spec.select48.i, %.not.i
  br label %.loopexit

.loopexit:                                        ; preds = %for.inc.2, %cleanup
  %5 = phi i32 [ %add, %cleanup ], [ 0, %for.inc.2 ]
  ret i32 %5

for.inc.1:                                        ; preds = %for.inc
  %6 = bitcast i256* %value to i64*
  %arrayidx.2 = getelementptr inbounds i64, i64* %6, i32 1
  %7 = load i64, i64* %arrayidx.2, align 8, !tbaa !4
  %tobool.not.2 = icmp eq i64 %7, 0
  br i1 %tobool.not.2, label %for.inc.2, label %cleanup

for.inc.2:                                        ; preds = %for.inc.1
  %8 = bitcast i256* %value to i64*
  %9 = load i64, i64* %8, align 8, !tbaa !4
  %tobool.not.3 = icmp eq i64 %9, 0
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
  %6 = icmp eq i64 %dividend.sroa.13.0.extract.trunc, 0
  %sub = sub nsw i32 %3, %5
  %sh_prom = zext i32 %sub to i256
  %shl = shl i256 %1, %sh_prom
  br i1 %6, label %for.inc.i96, label %cleanup.i127

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
  %7 = trunc i64 %v.addr.4.lobit.i.i123 to i32
  %.not.i.i124 = xor i32 %7, -1
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
  %8 = phi i32 [ %add.i126, %cleanup.i127 ], [ 0, %for.inc.2.i132 ]
  %9 = icmp eq i64 %divisor.sroa.10.0.extract.trunc, 0
  br i1 %9, label %for.inc.i54, label %cleanup.i85

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
  %10 = trunc i64 %v.addr.4.lobit.i.i81 to i32
  %.not.i.i82 = xor i32 %10, -1
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
  %11 = phi i32 [ %add.i84, %cleanup.i85 ], [ 0, %for.inc.2.i90 ]
  %cmp17 = icmp ugt i256 %shl, %0
  %shr = zext i1 %cmp17 to i256
  %sub14 = sub nsw i32 %8, %11
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
  %call = tail call i32 @udivmod256(i256* nonnull %pdividend, i256* nonnull %pdivisor, i256* %remainder, i256* %quotient) #19
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
  %7 = icmp slt i8 %1, 0
  br i1 %7, label %if.then24, label %cleanup

if.then24:                                        ; preds = %if.end22
  %8 = load i256, i256* %remainder, align 8, !tbaa !50
  %sub25 = sub i256 0, %8
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
  %2 = bitcast i512* %value to i64*
  %arrayidx.1 = getelementptr inbounds i64, i64* %2, i32 6
  %3 = load i64, i64* %arrayidx.1, align 8, !tbaa !4
  %tobool.not.1 = icmp eq i64 %3, 0
  br i1 %tobool.not.1, label %for.inc.1, label %cleanup

cleanup:                                          ; preds = %for.inc.6, %for.inc.5, %for.inc.4, %for.inc.3, %for.inc.2, %for.inc.1, %for.inc, %entry
  %i.013.lcssa = phi i32 [ 448, %entry ], [ 384, %for.inc ], [ 320, %for.inc.1 ], [ 256, %for.inc.2 ], [ 192, %for.inc.3 ], [ 128, %for.inc.4 ], [ 64, %for.inc.5 ], [ 0, %for.inc.6 ]
  %.lcssa = phi i64 [ %1, %entry ], [ %3, %for.inc ], [ %7, %for.inc.1 ], [ %9, %for.inc.2 ], [ %11, %for.inc.3 ], [ %13, %for.inc.4 ], [ %15, %for.inc.5 ], [ %17, %for.inc.6 ]
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
  %4 = trunc i64 %v.addr.4.lobit.i to i32
  %.not.i = xor i32 %4, -1
  %spec.select48.i = add nuw nsw i32 %h.4.i, %i.013.lcssa
  %add = add i32 %spec.select48.i, %.not.i
  br label %.loopexit

.loopexit:                                        ; preds = %for.inc.6, %cleanup
  %5 = phi i32 [ %add, %cleanup ], [ 0, %for.inc.6 ]
  ret i32 %5

for.inc.1:                                        ; preds = %for.inc
  %6 = bitcast i512* %value to i64*
  %arrayidx.2 = getelementptr inbounds i64, i64* %6, i32 5
  %7 = load i64, i64* %arrayidx.2, align 8, !tbaa !4
  %tobool.not.2 = icmp eq i64 %7, 0
  br i1 %tobool.not.2, label %for.inc.2, label %cleanup

for.inc.2:                                        ; preds = %for.inc.1
  %8 = bitcast i512* %value to i64*
  %arrayidx.3 = getelementptr inbounds i64, i64* %8, i32 4
  %9 = load i64, i64* %arrayidx.3, align 8, !tbaa !4
  %tobool.not.3 = icmp eq i64 %9, 0
  br i1 %tobool.not.3, label %for.inc.3, label %cleanup

for.inc.3:                                        ; preds = %for.inc.2
  %10 = bitcast i512* %value to i64*
  %arrayidx.4 = getelementptr inbounds i64, i64* %10, i32 3
  %11 = load i64, i64* %arrayidx.4, align 8, !tbaa !4
  %tobool.not.4 = icmp eq i64 %11, 0
  br i1 %tobool.not.4, label %for.inc.4, label %cleanup

for.inc.4:                                        ; preds = %for.inc.3
  %12 = bitcast i512* %value to i64*
  %arrayidx.5 = getelementptr inbounds i64, i64* %12, i32 2
  %13 = load i64, i64* %arrayidx.5, align 8, !tbaa !4
  %tobool.not.5 = icmp eq i64 %13, 0
  br i1 %tobool.not.5, label %for.inc.5, label %cleanup

for.inc.5:                                        ; preds = %for.inc.4
  %14 = bitcast i512* %value to i64*
  %arrayidx.6 = getelementptr inbounds i64, i64* %14, i32 1
  %15 = load i64, i64* %arrayidx.6, align 8, !tbaa !4
  %tobool.not.6 = icmp eq i64 %15, 0
  br i1 %tobool.not.6, label %for.inc.6, label %cleanup

for.inc.6:                                        ; preds = %for.inc.5
  %16 = bitcast i512* %value to i64*
  %17 = load i64, i64* %16, align 8, !tbaa !4
  %tobool.not.7 = icmp eq i64 %17, 0
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
  %6 = icmp eq i64 %dividend.sroa.21.0.extract.trunc, 0
  %sub = sub nsw i32 %3, %5
  %sh_prom = zext i32 %sub to i512
  %shl = shl i512 %1, %sh_prom
  br i1 %6, label %for.inc.i108, label %cleanup.i139

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
  %7 = trunc i64 %v.addr.4.lobit.i.i135 to i32
  %.not.i.i136 = xor i32 %7, -1
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
  %8 = phi i32 [ %add.i138, %cleanup.i139 ], [ 0, %for.inc.6.i156 ]
  %9 = icmp eq i64 %divisor.sroa.18.0.extract.trunc, 0
  br i1 %9, label %for.inc.i54, label %cleanup.i85

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
  %10 = trunc i64 %v.addr.4.lobit.i.i81 to i32
  %.not.i.i82 = xor i32 %10, -1
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
  %11 = phi i32 [ %add.i84, %cleanup.i85 ], [ 0, %for.inc.6.i102 ]
  %cmp17 = icmp ugt i512 %shl, %0
  %shr = zext i1 %cmp17 to i512
  %sub14 = sub nsw i32 %8, %11
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
  %call = tail call i32 @udivmod512(i512* nonnull %pdividend, i512* nonnull %pdivisor, i512* %remainder, i512* %quotient) #19
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
  %7 = icmp slt i8 %1, 0
  br i1 %7, label %if.then24, label %cleanup

if.then24:                                        ; preds = %if.end22
  %8 = load i512, i512* %remainder, align 8, !tbaa !52
  %sub25 = sub i512 0, %8
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
  br i1 %cmp34.not, label %for.cond.cleanup, label %for.body.preheader

for.body.preheader:                               ; preds = %entry
  br label %for.body

for.cond.cleanup:                                 ; preds = %for.body, %entry
  ret void

for.body:                                         ; preds = %for.body.preheader, %for.body
  %lsr.iv1 = phi i8* [ %input, %for.body.preheader ], [ %scevgep, %for.body ]
  %lsr.iv = phi i32 [ %length, %for.body.preheader ], [ %lsr.iv.next, %for.body ]
  %output.addr.036 = phi i8* [ %scevgep3, %for.body ], [ %output, %for.body.preheader ]
  %0 = load i8, i8* %lsr.iv1, align 1, !tbaa !12
  %1 = lshr i8 %0, 4
  %cmp3 = icmp ugt i8 %0, -97
  %sub = add nuw nsw i8 %1, 87
  %add7 = or i8 %1, 48
  %cond = select i1 %cmp3, i8 %sub, i8 %add7
  store i8 %cond, i8* %output.addr.036, align 1, !tbaa !12
  %2 = load i8, i8* %lsr.iv1, align 1, !tbaa !12
  %3 = and i8 %2, 15
  %cmp13 = icmp ugt i8 %3, 9
  %sub18 = add nuw nsw i8 %3, 87
  %add21 = or i8 %3, 48
  %cond23 = select i1 %cmp13, i8 %sub18, i8 %add21
  %scevgep2 = getelementptr i8, i8* %output.addr.036, i32 1
  store i8 %cond23, i8* %scevgep2, align 1, !tbaa !12
  %lsr.iv.next = add i32 %lsr.iv, -1
  %scevgep = getelementptr i8, i8* %lsr.iv1, i32 1
  %exitcond.not = icmp eq i32 %lsr.iv.next, 0
  %scevgep3 = getelementptr i8, i8* %output.addr.036, i32 2
  br i1 %exitcond.not, label %for.cond.cleanup, label %for.body
}

; Function Attrs: nofree norecurse nounwind
define hidden void @hex_encode_rev(i8* nocapture %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %i.035 = add i32 %length, -1
  %cmp36 = icmp sgt i32 %i.035, -1
  br i1 %cmp36, label %for.body.preheader, label %for.cond.cleanup

for.body.preheader:                               ; preds = %entry
  %scevgep = getelementptr i8, i8* %input, i32 -1
  br label %for.body

for.cond.cleanup:                                 ; preds = %for.body, %entry
  ret void

for.body:                                         ; preds = %for.body.preheader, %for.body
  %lsr.iv = phi i32 [ %length, %for.body.preheader ], [ %lsr.iv.next, %for.body ]
  %output.addr.037 = phi i8* [ %scevgep3, %for.body ], [ %output, %for.body.preheader ]
  %scevgep1 = getelementptr i8, i8* %scevgep, i32 %lsr.iv
  %0 = load i8, i8* %scevgep1, align 1, !tbaa !12
  %1 = lshr i8 %0, 4
  %cmp3 = icmp ugt i8 %0, -97
  %sub6 = add nuw nsw i8 %1, 87
  %add8 = or i8 %1, 48
  %cond = select i1 %cmp3, i8 %sub6, i8 %add8
  store i8 %cond, i8* %output.addr.037, align 1, !tbaa !12
  %2 = load i8, i8* %scevgep1, align 1, !tbaa !12
  %3 = and i8 %2, 15
  %cmp14 = icmp ugt i8 %3, 9
  %sub19 = add nuw nsw i8 %3, 87
  %add22 = or i8 %3, 48
  %cond24 = select i1 %cmp14, i8 %sub19, i8 %add22
  %scevgep2 = getelementptr i8, i8* %output.addr.037, i32 1
  store i8 %cond24, i8* %scevgep2, align 1, !tbaa !12
  %lsr.iv.next = add i32 %lsr.iv, -1
  %cmp = icmp sgt i32 %lsr.iv.next, 0
  %scevgep3 = getelementptr i8, i8* %output.addr.037, i32 2
  br i1 %cmp, label %for.body, label %for.cond.cleanup
}

; Function Attrs: nofree norecurse nounwind
define hidden nonnull i8* @uint2hex(i8* %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %0 = icmp ne i32 %length, 0
  %umin = zext i1 %0 to i32
  %scevgep3 = getelementptr i8, i8* %input, i32 -1
  br label %while.cond

while.cond:                                       ; preds = %land.rhs, %entry
  %length.addr.0 = phi i32 [ %length, %entry ], [ %sub, %land.rhs ]
  %cmp = icmp ugt i32 %length.addr.0, 1
  br i1 %cmp, label %land.rhs, label %while.cond.while.end_crit_edge

while.cond.while.end_crit_edge:                   ; preds = %while.cond
  %1 = icmp ne i32 %length, 0
  %not. = xor i1 %1, true
  %.pre112 = sext i1 %not. to i32
  br label %while.end

land.rhs:                                         ; preds = %while.cond
  %sub = add i32 %length.addr.0, -1
  %scevgep4 = getelementptr i8, i8* %scevgep3, i32 %length.addr.0
  %2 = load i8, i8* %scevgep4, align 1, !tbaa !12
  %cmp1 = icmp eq i8 %2, 0
  br i1 %cmp1, label %while.cond, label %while.end.loopexit

while.end.loopexit:                               ; preds = %land.rhs
  %3 = add i32 %sub, 1
  br label %while.end

while.end:                                        ; preds = %while.end.loopexit, %while.cond.while.end_crit_edge
  %sub4.pre-phi = phi i32 [ %.pre112, %while.cond.while.end_crit_edge ], [ %sub, %while.end.loopexit ]
  %length.addr.0.lcssa = phi i32 [ %umin, %while.cond.while.end_crit_edge ], [ %3, %while.end.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %output, i32 1
  store i8 48, i8* %output, align 1, !tbaa !12
  %incdec.ptr3 = getelementptr inbounds i8, i8* %output, i32 2
  store i8 120, i8* %incdec.ptr, align 1, !tbaa !12
  %arrayidx5 = getelementptr inbounds i8, i8* %input, i32 %sub4.pre-phi
  %4 = load i8, i8* %arrayidx5, align 1, !tbaa !12
  %5 = lshr i8 %4, 4
  %cmp9.not = icmp eq i8 %5, 0
  br i1 %cmp9.not, label %if.end, label %if.then

if.then:                                          ; preds = %while.end
  %cmp12 = icmp ugt i8 %4, -97
  %sub15 = add nuw nsw i8 %5, 87
  %add17 = or i8 %5, 48
  %cond = select i1 %cmp12, i8 %sub15, i8 %add17
  %incdec.ptr19 = getelementptr inbounds i8, i8* %output, i32 3
  %sunkaddr = getelementptr inbounds i8, i8* %output, i32 2
  store i8 %cond, i8* %sunkaddr, align 1, !tbaa !12
  %.pre = load i8, i8* %arrayidx5, align 1, !tbaa !12
  br label %if.end

if.end:                                           ; preds = %while.end, %if.then
  %6 = phi i8 [ %.pre, %if.then ], [ %4, %while.end ]
  %output.addr.0 = phi i8* [ %incdec.ptr19, %if.then ], [ %incdec.ptr3, %while.end ]
  %7 = and i8 %6, 15
  %cmp25 = icmp ugt i8 %7, 9
  %sub30 = add nuw nsw i8 %7, 87
  %add33 = or i8 %7, 48
  %cond35 = select i1 %cmp25, i8 %sub30, i8 %add33
  store i8 %cond35, i8* %output.addr.0, align 1, !tbaa !12
  %output.addr.1104 = getelementptr inbounds i8, i8* %output.addr.0, i32 1
  %tobool.not106 = icmp eq i32 %sub4.pre-phi, 0
  br i1 %tobool.not106, label %while.end81, label %while.body40.preheader

while.body40.preheader:                           ; preds = %if.end
  br label %while.body40

while.body40:                                     ; preds = %while.body40.preheader, %while.body40
  %lsr.iv = phi i8* [ %output.addr.1104, %while.body40.preheader ], [ %scevgep2, %while.body40 ]
  %dec39110 = phi i32 [ %dec39, %while.body40 ], [ %sub4.pre-phi, %while.body40.preheader ]
  %length.addr.1107 = phi i32 [ %dec39110, %while.body40 ], [ %length.addr.0.lcssa, %while.body40.preheader ]
  %sub42 = add i32 %length.addr.1107, -2
  %arrayidx43 = getelementptr inbounds i8, i8* %input, i32 %sub42
  %8 = load i8, i8* %arrayidx43, align 1, !tbaa !12
  %9 = lshr i8 %8, 4
  %cmp48 = icmp ugt i8 %8, -97
  %sub53 = add nuw nsw i8 %9, 87
  %add56 = or i8 %9, 48
  %cond58 = select i1 %cmp48, i8 %sub53, i8 %add56
  store i8 %cond58, i8* %lsr.iv, align 1, !tbaa !12
  %10 = load i8, i8* %arrayidx43, align 1, !tbaa !12
  %11 = and i8 %10, 15
  %cmp68 = icmp ugt i8 %11, 9
  %sub73 = add nuw nsw i8 %11, 87
  %add76 = or i8 %11, 48
  %cond78 = select i1 %cmp68, i8 %sub73, i8 %add76
  %scevgep1 = getelementptr i8, i8* %lsr.iv, i32 1
  store i8 %cond78, i8* %scevgep1, align 1, !tbaa !12
  %dec39 = add i32 %dec39110, -1
  %scevgep = getelementptr i8, i8* %lsr.iv, i32 2
  %tobool.not = icmp eq i32 %dec39, 0
  %scevgep2 = getelementptr i8, i8* %lsr.iv, i32 2
  br i1 %tobool.not, label %while.end81, label %while.body40

while.end81:                                      ; preds = %while.body40, %if.end
  %output.addr.1.lcssa = phi i8* [ %output.addr.1104, %if.end ], [ %scevgep, %while.body40 ]
  ret i8* %output.addr.1.lcssa
}

; Function Attrs: nofree norecurse nounwind
define hidden nonnull i8* @uint2bin(i8* %output, i8* nocapture readonly %input, i32 %length) local_unnamed_addr #12 {
entry:
  %0 = icmp ne i32 %length, 0
  %umin = zext i1 %0 to i32
  %scevgep8 = getelementptr i8, i8* %input, i32 -1
  br label %while.cond

while.cond:                                       ; preds = %land.rhs, %entry
  %length.addr.0 = phi i32 [ %length, %entry ], [ %sub, %land.rhs ]
  %cmp = icmp ugt i32 %length.addr.0, 1
  br i1 %cmp, label %land.rhs, label %while.cond.while.end_crit_edge

while.cond.while.end_crit_edge:                   ; preds = %while.cond
  %1 = icmp ne i32 %length, 0
  %not. = xor i1 %1, true
  %.pre = sext i1 %not. to i32
  br label %while.end

land.rhs:                                         ; preds = %while.cond
  %sub = add i32 %length.addr.0, -1
  %scevgep9 = getelementptr i8, i8* %scevgep8, i32 %length.addr.0
  %2 = load i8, i8* %scevgep9, align 1, !tbaa !12
  %cmp1 = icmp eq i8 %2, 0
  br i1 %cmp1, label %while.cond, label %while.end.loopexit

while.end.loopexit:                               ; preds = %land.rhs
  %3 = add i32 %sub, 1
  br label %while.end

while.end:                                        ; preds = %while.end.loopexit, %while.cond.while.end_crit_edge
  %sub4.pre-phi = phi i32 [ %.pre, %while.cond.while.end_crit_edge ], [ %sub, %while.end.loopexit ]
  %length.addr.0.lcssa = phi i32 [ %umin, %while.cond.while.end_crit_edge ], [ %3, %while.end.loopexit ]
  %incdec.ptr = getelementptr inbounds i8, i8* %output, i32 1
  store i8 48, i8* %output, align 1, !tbaa !12
  %incdec.ptr3 = getelementptr inbounds i8, i8* %output, i32 2
  store i8 98, i8* %incdec.ptr, align 1, !tbaa !12
  %arrayidx5 = getelementptr inbounds i8, i8* %input, i32 %sub4.pre-phi
  %4 = load i8, i8* %arrayidx5, align 1, !tbaa !12
  %tobool.not82 = icmp sgt i8 %4, -1
  br i1 %tobool.not82, label %while.body12.preheader, label %while.body20.preheader

while.body12.preheader:                           ; preds = %while.end
  br label %while.body12

while.cond17.preheader:                           ; preds = %while.body12
  %tobool19.not77 = icmp eq i32 %dec15, 0
  br i1 %tobool19.not77, label %while.cond30.preheader, label %while.body20.preheader

while.body20.preheader:                           ; preds = %while.cond17.preheader, %while.end
  %i.180.ph = phi i32 [ 8, %while.end ], [ %dec15, %while.cond17.preheader ]
  %v.179.ph = phi i8 [ %4, %while.end ], [ %shl, %while.cond17.preheader ]
  br label %while.body20

while.body12:                                     ; preds = %while.body12.preheader, %while.body12
  %i.084 = phi i32 [ %dec15, %while.body12 ], [ 8, %while.body12.preheader ]
  %v.083 = phi i8 [ %shl, %while.body12 ], [ %4, %while.body12.preheader ]
  %shl = shl nuw i8 %v.083, 1
  %dec15 = add nsw i32 %i.084, -1
  %cmp7 = icmp ugt i32 %i.084, 1
  %tobool.not = icmp sgt i8 %shl, -1
  %5 = and i1 %tobool.not, %cmp7
  br i1 %5, label %while.body12, label %while.cond17.preheader

while.cond30.preheader:                           ; preds = %while.body20, %while.cond17.preheader
  %output.addr.0.lcssa = phi i8* [ %incdec.ptr3, %while.cond17.preheader ], [ %incdec.ptr25, %while.body20 ]
  %tobool32.not73 = icmp eq i32 %sub4.pre-phi, 0
  br i1 %tobool32.not73, label %while.end48, label %while.body33.preheader

while.body33.preheader:                           ; preds = %while.cond30.preheader
  br label %while.body33

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

while.body33:                                     ; preds = %while.body33.preheader, %while.body33
  %dec3176 = phi i32 [ %dec31, %while.body33 ], [ %sub4.pre-phi, %while.body33.preheader ]
  %length.addr.175 = phi i32 [ %dec3176, %while.body33 ], [ %length.addr.0.lcssa, %while.body33.preheader ]
  %output.addr.174 = phi i8* [ %scevgep7, %while.body33 ], [ %output.addr.0.lcssa, %while.body33.preheader ]
  %sub35 = add i32 %length.addr.175, -2
  %arrayidx36 = getelementptr inbounds i8, i8* %input, i32 %sub35
  %6 = load i8, i8* %arrayidx36, align 1, !tbaa !12
  %tobool41.not = icmp sgt i8 %6, -1
  %conv43 = select i1 %tobool41.not, i8 48, i8 49
  store i8 %conv43, i8* %output.addr.174, align 1, !tbaa !12
  %shl46.mask = and i8 %6, 64
  %tobool41.not.1 = icmp eq i8 %shl46.mask, 0
  %conv43.1 = select i1 %tobool41.not.1, i8 48, i8 49
  %scevgep = getelementptr i8, i8* %output.addr.174, i32 1
  store i8 %conv43.1, i8* %scevgep, align 1, !tbaa !12
  %shl46.1.mask = and i8 %6, 32
  %tobool41.not.2 = icmp eq i8 %shl46.1.mask, 0
  %conv43.2 = select i1 %tobool41.not.2, i8 48, i8 49
  %scevgep1 = getelementptr i8, i8* %output.addr.174, i32 2
  store i8 %conv43.2, i8* %scevgep1, align 1, !tbaa !12
  %shl46.2.mask = and i8 %6, 16
  %tobool41.not.3 = icmp eq i8 %shl46.2.mask, 0
  %conv43.3 = select i1 %tobool41.not.3, i8 48, i8 49
  %scevgep2 = getelementptr i8, i8* %output.addr.174, i32 3
  store i8 %conv43.3, i8* %scevgep2, align 1, !tbaa !12
  %shl46.3.mask = and i8 %6, 8
  %tobool41.not.4 = icmp eq i8 %shl46.3.mask, 0
  %conv43.4 = select i1 %tobool41.not.4, i8 48, i8 49
  %scevgep3 = getelementptr i8, i8* %output.addr.174, i32 4
  store i8 %conv43.4, i8* %scevgep3, align 1, !tbaa !12
  %shl46.4.mask = and i8 %6, 4
  %tobool41.not.5 = icmp eq i8 %shl46.4.mask, 0
  %conv43.5 = select i1 %tobool41.not.5, i8 48, i8 49
  %scevgep4 = getelementptr i8, i8* %output.addr.174, i32 5
  store i8 %conv43.5, i8* %scevgep4, align 1, !tbaa !12
  %shl46.5.mask = and i8 %6, 2
  %tobool41.not.6 = icmp eq i8 %shl46.5.mask, 0
  %conv43.6 = select i1 %tobool41.not.6, i8 48, i8 49
  %scevgep5 = getelementptr i8, i8* %output.addr.174, i32 6
  store i8 %conv43.6, i8* %scevgep5, align 1, !tbaa !12
  %shl46.6.mask = and i8 %6, 1
  %7 = or i8 %shl46.6.mask, 48
  %incdec.ptr44.7 = getelementptr inbounds i8, i8* %output.addr.174, i32 8
  %scevgep6 = getelementptr i8, i8* %output.addr.174, i32 7
  store i8 %7, i8* %scevgep6, align 1, !tbaa !12
  %dec31 = add i32 %dec3176, -1
  %tobool32.not = icmp eq i32 %dec31, 0
  %scevgep7 = getelementptr i8, i8* %output.addr.174, i32 8
  br i1 %tobool32.not, label %while.end48, label %while.body33

while.end48:                                      ; preds = %while.body33, %while.cond30.preheader
  %output.addr.1.lcssa = phi i8* [ %output.addr.0.lcssa, %while.cond30.preheader ], [ %incdec.ptr44.7, %while.body33 ]
  ret i8* %output.addr.1.lcssa
}

; Function Attrs: nounwind writeonly
define hidden i8* @uint2dec(i8* %output, i64 %val) local_unnamed_addr #14 {
entry:
  %buf = alloca [20 x i8], align 16
  %0 = bitcast [20 x i8]* %buf to i8*
  call void @llvm.lifetime.start.p0i8(i64 20, i8* nonnull %0) #20
  br label %do.body

do.body:                                          ; preds = %do.body, %entry
  %val.addr.0 = phi i64 [ %val, %entry ], [ %div, %do.body ]
  %len.0 = phi i32 [ 0, %entry ], [ %inc, %do.body ]
  %val.addr.0.frozen = freeze i64 %val.addr.0
  %div = udiv i64 %val.addr.0.frozen, 10
  %1 = mul i64 %div, 10
  %rem.decomposed = sub i64 %val.addr.0.frozen, %1
  %conv = trunc i64 %rem.decomposed to i8
  %inc = add nuw i32 %len.0, 1
  %scevgep4 = getelementptr [20 x i8], [20 x i8]* %buf, i32 0, i32 %len.0
  store i8 %conv, i8* %scevgep4, align 1, !tbaa !12
  %2 = icmp ult i64 %val.addr.0, 10
  br i1 %2, label %while.body.preheader, label %do.body

while.body.preheader:                             ; preds = %do.body
  %add14 = or i8 %conv, 48
  %incdec.ptr15 = getelementptr inbounds i8, i8* %output, i32 1
  store i8 %add14, i8* %output, align 1, !tbaa !12
  %tobool1.not17 = icmp eq i32 %inc, 1
  br i1 %tobool1.not17, label %while.end, label %while.body.while.body_crit_edge.preheader

while.body.while.body_crit_edge.preheader:        ; preds = %while.body.preheader
  %scevgep = getelementptr [20 x i8], [20 x i8]* %buf, i32 0, i32 -2
  br label %while.body.while.body_crit_edge

while.body.while.body_crit_edge:                  ; preds = %while.body.while.body_crit_edge.preheader, %while.body.while.body_crit_edge
  %lsr.iv1 = phi i32 [ %inc, %while.body.while.body_crit_edge.preheader ], [ %lsr.iv.next2, %while.body.while.body_crit_edge ]
  %incdec.ptr18 = phi i8* [ %incdec.ptr, %while.body.while.body_crit_edge ], [ %incdec.ptr15, %while.body.while.body_crit_edge.preheader ]
  %scevgep3 = getelementptr i8, i8* %scevgep, i32 %lsr.iv1
  %.pre = load i8, i8* %scevgep3, align 1, !tbaa !12
  %add = add i8 %.pre, 48
  %incdec.ptr = getelementptr inbounds i8, i8* %incdec.ptr18, i32 1
  store i8 %add, i8* %incdec.ptr18, align 1, !tbaa !12
  %lsr.iv.next2 = add i32 %lsr.iv1, -1
  %tobool1.not = icmp eq i32 %lsr.iv.next2, 1
  br i1 %tobool1.not, label %while.end, label %while.body.while.body_crit_edge

while.end:                                        ; preds = %while.body.while.body_crit_edge, %while.body.preheader
  %incdec.ptr.lcssa = phi i8* [ %incdec.ptr15, %while.body.preheader ], [ %incdec.ptr, %while.body.while.body_crit_edge ]
  %3 = bitcast [20 x i8]* %buf to i8*
  call void @llvm.lifetime.end.p0i8(i64 20, i8* nonnull %3) #20
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
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %0) #20
  store i128 10000000000000000000, i128* %divisor, align 16, !tbaa !48
  %1 = bitcast i128* %q to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %1) #20
  %2 = bitcast i128* %r to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %2) #20
  %3 = bitcast [40 x i8]* %buf to i8*
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %3) #20
  %4 = load i128, i128* %val128.addr, align 16, !tbaa !48
  %5 = load i128, i128* %divisor, align 16, !tbaa !48
  switch i128 %5, label %if.end3.i [
    i128 0, label %udivmod128.exit
    i128 1, label %if.then2.i
  ]

if.then2.i:                                       ; preds = %entry
  store i128 0, i128* %r, align 16, !tbaa !48
  store i128 %4, i128* %q, align 16, !tbaa !48
  br label %udivmod128.exit

if.end3.i:                                        ; preds = %entry
  %cmp4.i = icmp eq i128 %5, %4
  br i1 %cmp4.i, label %if.then5.i, label %if.end6.i

if.then5.i:                                       ; preds = %if.end3.i
  store i128 0, i128* %r, align 16, !tbaa !48
  store i128 1, i128* %q, align 16, !tbaa !48
  br label %udivmod128.exit

if.end6.i:                                        ; preds = %if.end3.i
  %cmp7.i = icmp eq i128 %4, 0
  %cmp8.i = icmp ult i128 %4, %5
  %or.cond.i = or i1 %cmp7.i, %cmp8.i
  br i1 %or.cond.i, label %if.then9.i, label %if.end10.i

if.then9.i:                                       ; preds = %if.end6.i
  store i128 %4, i128* %r, align 16, !tbaa !48
  store i128 0, i128* %q, align 16, !tbaa !48
  br label %udivmod128.exit

if.end10.i:                                       ; preds = %if.end6.i
  %call.i = call i32 @bits128(i128 %4) #18
  %cmp1152.i = icmp sgt i32 %call.i, -1
  br i1 %cmp1152.i, label %for.body.preheader.i, label %for.cond.cleanup.i

for.body.preheader.i:                             ; preds = %if.end10.i
  br label %for.body.i

for.cond.cleanup.i:                               ; preds = %for.body.i, %if.end10.i
  %q.0.lcssa.i = phi i128 [ 0, %if.end10.i ], [ %q.1.i, %for.body.i ]
  %r.0.lcssa.i = phi i128 [ 0, %if.end10.i ], [ %r.2.i, %for.body.i ]
  store i128 %q.0.lcssa.i, i128* %q, align 16, !tbaa !48
  store i128 %r.0.lcssa.i, i128* %r, align 16, !tbaa !48
  br label %udivmod128.exit

for.body.i:                                       ; preds = %for.body.i, %for.body.preheader.i
  %lsr.iv44 = phi i32 [ %lsr.iv.next45, %for.body.i ], [ %call.i, %for.body.preheader.i ]
  %r.054.i = phi i128 [ %r.2.i, %for.body.i ], [ 0, %for.body.preheader.i ]
  %q.053.i = phi i128 [ %q.1.i, %for.body.i ], [ 0, %for.body.preheader.i ]
  %shl.i = shl i128 %q.053.i, 1
  %shl12.i = shl i128 %r.054.i, 1
  %sh_prom.i = zext i32 %lsr.iv44 to i128
  %6 = shl nuw i128 1, %sh_prom.i
  %7 = and i128 %6, %4
  %tobool.not.i = icmp ne i128 %7, 0
  %inc.i = zext i1 %tobool.not.i to i128
  %spec.select.i = or i128 %shl12.i, %inc.i
  %cmp15.not.i = icmp ult i128 %spec.select.i, %5
  %not.cmp15.not.i = xor i1 %cmp15.not.i, true
  %inc18.i = zext i1 %not.cmp15.not.i to i128
  %q.1.i = or i128 %shl.i, %inc18.i
  %sub17.i = select i1 %cmp15.not.i, i128 0, i128 %5
  %r.2.i = sub i128 %spec.select.i, %sub17.i
  %lsr.iv.next45 = add nsw i32 %lsr.iv44, -1
  %8 = add i32 %lsr.iv.next45, 2
  %cmp11.i = icmp sgt i32 %8, 1
  br i1 %cmp11.i, label %for.body.i, label %for.cond.cleanup.i

udivmod128.exit:                                  ; preds = %entry, %if.then2.i, %if.then5.i, %if.then9.i, %for.cond.cleanup.i
  %retval.0.i = phi i32 [ 0, %if.then2.i ], [ 0, %if.then5.i ], [ 0, %if.then9.i ], [ 0, %for.cond.cleanup.i ], [ 1, %entry ]
  %9 = load i128, i128* %r, align 16, !tbaa !48
  %conv = trunc i128 %9 to i64
  br label %do.body

do.body:                                          ; preds = %do.body, %udivmod128.exit
  %len.0 = phi i32 [ 0, %udivmod128.exit ], [ %inc, %do.body ]
  %val.0 = phi i64 [ %conv, %udivmod128.exit ], [ %div, %do.body ]
  %val.0.frozen = freeze i64 %val.0
  %div = udiv i64 %val.0.frozen, 10
  %10 = mul i64 %div, 10
  %rem.decomposed = sub i64 %val.0.frozen, %10
  %conv1 = trunc i64 %rem.decomposed to i8
  %inc = add nuw i32 %len.0, 1
  %scevgep43 = getelementptr [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.0
  store i8 %conv1, i8* %scevgep43, align 1, !tbaa !12
  %11 = icmp ult i64 %val.0, 10
  br i1 %11, label %do.end, label %do.body

do.end:                                           ; preds = %do.body
  %12 = load i128, i128* %q, align 16, !tbaa !48
  %13 = load i128, i128* %divisor, align 16, !tbaa !48
  %14 = add i32 %inc, -1
  switch i128 %13, label %if.end3.i3 [
    i128 0, label %udivmod128.exit37
    i128 1, label %if.then2.i1
  ]

if.then2.i1:                                      ; preds = %do.end
  store i128 0, i128* %r, align 16, !tbaa !48
  store i128 %12, i128* %q, align 16, !tbaa !48
  br label %udivmod128.exit37

if.end3.i3:                                       ; preds = %do.end
  %cmp4.i2 = icmp eq i128 %13, %12
  br i1 %cmp4.i2, label %if.then5.i4, label %if.end6.i8

if.then5.i4:                                      ; preds = %if.end3.i3
  store i128 0, i128* %r, align 16, !tbaa !48
  store i128 1, i128* %q, align 16, !tbaa !48
  br label %udivmod128.exit37

if.end6.i8:                                       ; preds = %if.end3.i3
  %cmp7.i5 = icmp eq i128 %12, 0
  %cmp8.i6 = icmp ult i128 %12, %13
  %or.cond.i7 = or i1 %cmp7.i5, %cmp8.i6
  br i1 %or.cond.i7, label %if.then9.i9, label %if.end10.i12

if.then9.i9:                                      ; preds = %if.end6.i8
  store i128 %12, i128* %r, align 16, !tbaa !48
  store i128 0, i128* %q, align 16, !tbaa !48
  br label %udivmod128.exit37

if.end10.i12:                                     ; preds = %if.end6.i8
  %call.i10 = call i32 @bits128(i128 %12) #18
  %cmp1152.i11 = icmp sgt i32 %call.i10, -1
  br i1 %cmp1152.i11, label %for.body.preheader.i14, label %for.cond.cleanup.i17

for.body.preheader.i14:                           ; preds = %if.end10.i12
  br label %for.body.i35

for.cond.cleanup.i17:                             ; preds = %for.body.i35, %if.end10.i12
  %q.0.lcssa.i15 = phi i128 [ 0, %if.end10.i12 ], [ %q.1.i31, %for.body.i35 ]
  %r.0.lcssa.i16 = phi i128 [ 0, %if.end10.i12 ], [ %r.2.i33, %for.body.i35 ]
  store i128 %q.0.lcssa.i15, i128* %q, align 16, !tbaa !48
  store i128 %r.0.lcssa.i16, i128* %r, align 16, !tbaa !48
  br label %udivmod128.exit37

for.body.i35:                                     ; preds = %for.body.i35, %for.body.preheader.i14
  %lsr.iv = phi i32 [ %lsr.iv.next, %for.body.i35 ], [ %call.i10, %for.body.preheader.i14 ]
  %r.054.i19 = phi i128 [ %r.2.i33, %for.body.i35 ], [ 0, %for.body.preheader.i14 ]
  %q.053.i20 = phi i128 [ %q.1.i31, %for.body.i35 ], [ 0, %for.body.preheader.i14 ]
  %shl.i21 = shl i128 %q.053.i20, 1
  %shl12.i22 = shl i128 %r.054.i19, 1
  %sh_prom.i24 = zext i32 %lsr.iv to i128
  %15 = shl nuw i128 1, %sh_prom.i24
  %16 = and i128 %15, %12
  %tobool.not.i25 = icmp ne i128 %16, 0
  %inc.i26 = zext i1 %tobool.not.i25 to i128
  %spec.select.i27 = or i128 %shl12.i22, %inc.i26
  %cmp15.not.i28 = icmp ult i128 %spec.select.i27, %13
  %not.cmp15.not.i29 = xor i1 %cmp15.not.i28, true
  %inc18.i30 = zext i1 %not.cmp15.not.i29 to i128
  %q.1.i31 = or i128 %shl.i21, %inc18.i30
  %sub17.i32 = select i1 %cmp15.not.i28, i128 0, i128 %13
  %r.2.i33 = sub i128 %spec.select.i27, %sub17.i32
  %lsr.iv.next = add nsw i32 %lsr.iv, -1
  %17 = add i32 %lsr.iv.next, 2
  %cmp11.i34 = icmp sgt i32 %17, 1
  br i1 %cmp11.i34, label %for.body.i35, label %for.cond.cleanup.i17

udivmod128.exit37:                                ; preds = %do.end, %if.then2.i1, %if.then5.i4, %if.then9.i9, %for.cond.cleanup.i17
  %retval.0.i36 = phi i32 [ 0, %if.then2.i1 ], [ 0, %if.then5.i4 ], [ 0, %if.then9.i9 ], [ 0, %for.cond.cleanup.i17 ], [ 1, %do.end ]
  %18 = load i128, i128* %r, align 16, !tbaa !48
  %conv3 = trunc i128 %18 to i64
  %tobool4.not = icmp eq i64 %conv3, 0
  br i1 %tobool4.not, label %if.end, label %while.cond.preheader

while.cond.preheader:                             ; preds = %udivmod128.exit37
  %cmp73 = icmp ult i32 %14, 18
  br i1 %cmp73, label %while.body.preheader, label %do.body8.preheader

while.body.preheader:                             ; preds = %while.cond.preheader
  br label %while.body

while.body:                                       ; preds = %while.body.preheader, %while.body
  %len.174 = phi i32 [ %inc6, %while.body ], [ %inc, %while.body.preheader ]
  %inc6 = add i32 %len.174, 1
  %scevgep42 = getelementptr [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.174
  store i8 0, i8* %scevgep42, align 1, !tbaa !12
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
  %19 = mul i64 %div13, 10
  %rem9.decomposed = sub i64 %val.1.frozen, %19
  %conv10 = trunc i64 %rem9.decomposed to i8
  %inc11 = add i32 %len.2, 1
  %scevgep41 = getelementptr [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.2
  store i8 %conv10, i8* %scevgep41, align 1, !tbaa !12
  %20 = icmp ult i64 %val.1, 10
  br i1 %20, label %if.end, label %do.body8

if.end:                                           ; preds = %do.body8, %udivmod128.exit37
  %len.3 = phi i32 [ %inc, %udivmod128.exit37 ], [ %inc11, %do.body8 ]
  %21 = load i128, i128* %q, align 16, !tbaa !48
  %conv17 = trunc i128 %21 to i64
  %tobool18.not = icmp eq i64 %conv17, 0
  br i1 %tobool18.not, label %while.body39.preheader, label %while.cond20.preheader

while.cond20.preheader:                           ; preds = %if.end
  %cmp2170 = icmp slt i32 %len.3, 38
  br i1 %cmp2170, label %while.body23.preheader, label %do.body27.preheader

while.body23.preheader:                           ; preds = %while.cond20.preheader
  br label %while.body23

while.body23:                                     ; preds = %while.body23.preheader, %while.body23
  %len.471 = phi i32 [ %inc24, %while.body23 ], [ %len.3, %while.body23.preheader ]
  %inc24 = add i32 %len.471, 1
  %scevgep40 = getelementptr [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.471
  store i8 0, i8* %scevgep40, align 1, !tbaa !12
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
  %22 = mul i64 %div32, 10
  %rem28.decomposed = sub i64 %val.2.frozen, %22
  %conv29 = trunc i64 %rem28.decomposed to i8
  %inc30 = add i32 %len.5, 1
  %scevgep39 = getelementptr [40 x i8], [40 x i8]* %buf, i32 0, i32 %len.5
  store i8 %conv29, i8* %scevgep39, align 1, !tbaa !12
  %23 = icmp ult i64 %val.2, 10
  br i1 %23, label %if.end36, label %do.body27

if.end36:                                         ; preds = %do.body27
  %tobool38.not67 = icmp eq i32 %inc30, 0
  br i1 %tobool38.not67, label %while.end43, label %while.body39.preheader

while.body39.preheader:                           ; preds = %if.end36, %if.end
  %dec69.in.ph = phi i32 [ %len.3, %if.end ], [ %inc30, %if.end36 ]
  %scevgep = getelementptr [40 x i8], [40 x i8]* %buf, i32 0, i32 -1
  br label %while.body39

while.body39:                                     ; preds = %while.body39.preheader, %while.body39
  %dec69.in = phi i32 [ %dec69, %while.body39 ], [ %dec69.in.ph, %while.body39.preheader ]
  %output.addr.068 = phi i8* [ %incdec.ptr, %while.body39 ], [ %output, %while.body39.preheader ]
  %dec69 = add nsw i32 %dec69.in, -1
  %scevgep38 = getelementptr i8, i8* %scevgep, i32 %dec69.in
  %24 = load i8, i8* %scevgep38, align 1, !tbaa !12
  %add = add i8 %24, 48
  %incdec.ptr = getelementptr inbounds i8, i8* %output.addr.068, i32 1
  store i8 %add, i8* %output.addr.068, align 1, !tbaa !12
  %tobool38.not = icmp eq i32 %dec69, 0
  br i1 %tobool38.not, label %while.end43, label %while.body39

while.end43:                                      ; preds = %while.body39, %if.end36
  %output.addr.0.lcssa = phi i8* [ %output, %if.end36 ], [ %incdec.ptr, %while.body39 ]
  %25 = bitcast [40 x i8]* %buf to i8*
  %26 = bitcast i128* %r to i8*
  %27 = bitcast i128* %q to i8*
  %28 = bitcast i128* %divisor to i8*
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %25) #20
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %26) #20
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %27) #20
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %28) #20
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
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %0) #20
  store i256 10000000000000000000, i256* %divisor, align 8, !tbaa !50
  %1 = bitcast i256* %q to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %1) #20
  %2 = load i256, i256* %val256, align 8, !tbaa !50
  store i256 %2, i256* %q, align 8, !tbaa !50
  %3 = bitcast i256* %r to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %3) #20
  %4 = bitcast [80 x i8]* %buf to i8*
  call void @llvm.lifetime.start.p0i8(i64 80, i8* nonnull %4) #20
  %call = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #18
  %5 = load i256, i256* %r, align 8, !tbaa !50
  %conv = trunc i256 %5 to i64
  br label %do.body

for.cond:                                         ; preds = %do.end
  %call.1 = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #18
  %6 = load i256, i256* %r, align 8, !tbaa !50
  %conv.1 = trunc i256 %6 to i64
  %cmp162.1 = icmp ult i32 %10, 18
  br i1 %cmp162.1, label %while.body.1.preheader, label %do.body.1.preheader

while.body.1.preheader:                           ; preds = %for.cond
  br label %while.body.1

do.body:                                          ; preds = %do.body.preheader, %do.body
  %len.2 = phi i32 [ %inc4, %do.body ], [ 0, %do.body.preheader ]
  %val.0 = phi i64 [ %div, %do.body ], [ %conv, %do.body.preheader ]
  %val.0.frozen = freeze i64 %val.0
  %div = udiv i64 %val.0.frozen, 10
  %7 = mul i64 %div, 10
  %rem.decomposed = sub i64 %val.0.frozen, %7
  %conv3 = trunc i64 %rem.decomposed to i8
  %inc4 = add nuw i32 %len.2, 1
  %scevgep9 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2
  store i8 %conv3, i8* %scevgep9, align 1, !tbaa !12
  %8 = icmp ult i64 %val.0, 10
  br i1 %8, label %do.end, label %do.body

do.end:                                           ; preds = %do.body
  %9 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not = icmp eq i256 %9, 0
  %10 = add i32 %inc4, -1
  br i1 %cmp6.not, label %while.body25.preheader, label %for.cond

cleanup8:                                         ; preds = %do.end.3
  %extract.t = trunc i256 %30 to i64
  %tobool11.not = icmp eq i64 %extract.t, 0
  br i1 %tobool11.not, label %if.end22, label %do.body13.preheader

do.body13.preheader:                              ; preds = %cleanup8
  br label %do.body13

do.body13:                                        ; preds = %do.body13.preheader, %do.body13
  %len.4 = phi i32 [ %inc16, %do.body13 ], [ %inc4.3, %do.body13.preheader ]
  %val9.0 = phi i64 [ %div18, %do.body13 ], [ %extract.t, %do.body13.preheader ]
  %val9.0.frozen = freeze i64 %val9.0
  %div18 = udiv i64 %val9.0.frozen, 10
  %11 = mul i64 %div18, 10
  %rem14.decomposed = sub i64 %val9.0.frozen, %11
  %conv15 = trunc i64 %rem14.decomposed to i8
  %inc16 = add i32 %len.4, 1
  %scevgep2 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.4
  store i8 %conv15, i8* %scevgep2, align 1, !tbaa !12
  %12 = icmp ult i64 %val9.0, 10
  br i1 %12, label %if.end22, label %do.body13

if.end22:                                         ; preds = %do.end.3, %do.end.2, %do.end.1, %do.body13, %cleanup8
  %len.5 = phi i32 [ %inc4.3, %cleanup8 ], [ %inc16, %do.body13 ], [ %inc4.1, %do.end.1 ], [ %inc4.2, %do.end.2 ], [ %inc4.3, %do.end.3 ]
  %tobool24.not59 = icmp eq i32 %len.5, 0
  br i1 %tobool24.not59, label %while.end30, label %while.body25.preheader

while.body25.preheader:                           ; preds = %do.end, %if.end22
  %dec61.in.ph = phi i32 [ %len.5, %if.end22 ], [ %inc4, %do.end ]
  %scevgep = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 -1
  br label %while.body25

while.body25:                                     ; preds = %while.body25.preheader, %while.body25
  %dec61.in = phi i32 [ %dec61, %while.body25 ], [ %dec61.in.ph, %while.body25.preheader ]
  %output.addr.060 = phi i8* [ %incdec.ptr, %while.body25 ], [ %output, %while.body25.preheader ]
  %dec61 = add nsw i32 %dec61.in, -1
  %scevgep1 = getelementptr i8, i8* %scevgep, i32 %dec61.in
  %13 = load i8, i8* %scevgep1, align 1, !tbaa !12
  %add28 = add i8 %13, 48
  %incdec.ptr = getelementptr inbounds i8, i8* %output.addr.060, i32 1
  store i8 %add28, i8* %output.addr.060, align 1, !tbaa !12
  %tobool24.not = icmp eq i32 %dec61, 0
  br i1 %tobool24.not, label %while.end30, label %while.body25

while.end30:                                      ; preds = %while.body25, %if.end22
  %output.addr.0.lcssa = phi i8* [ %output, %if.end22 ], [ %incdec.ptr, %while.body25 ]
  %14 = bitcast [80 x i8]* %buf to i8*
  %15 = bitcast i256* %r to i8*
  %16 = bitcast i256* %q to i8*
  %17 = bitcast i256* %divisor to i8*
  call void @llvm.lifetime.end.p0i8(i64 80, i8* nonnull %14) #20
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %15) #20
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %16) #20
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %17) #20
  ret i8* %output.addr.0.lcssa

while.body.1:                                     ; preds = %while.body.1.preheader, %while.body.1
  %len.163.1 = phi i32 [ %inc.1, %while.body.1 ], [ %inc4, %while.body.1.preheader ]
  %inc.1 = add nuw nsw i32 %len.163.1, 1
  %scevgep8 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.163.1
  store i8 0, i8* %scevgep8, align 1, !tbaa !12
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
  %18 = mul i64 %div.1, 10
  %rem.1.decomposed = sub i64 %val.0.1.frozen, %18
  %conv3.1 = trunc i64 %rem.1.decomposed to i8
  %inc4.1 = add i32 %len.2.1, 1
  %scevgep7 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2.1
  store i8 %conv3.1, i8* %scevgep7, align 1, !tbaa !12
  %19 = icmp ult i64 %val.0.1, 10
  br i1 %19, label %do.end.1, label %do.body.1

do.end.1:                                         ; preds = %do.body.1
  %20 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not.1 = icmp eq i256 %20, 0
  %21 = add i32 %inc4.1, -1
  br i1 %cmp6.not.1, label %if.end22, label %for.cond.1

for.cond.1:                                       ; preds = %do.end.1
  %call.2 = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #18
  %22 = load i256, i256* %r, align 8, !tbaa !50
  %conv.2 = trunc i256 %22 to i64
  %cmp162.2 = icmp slt i32 %21, 37
  br i1 %cmp162.2, label %while.body.2.preheader, label %do.body.2.preheader

while.body.2.preheader:                           ; preds = %for.cond.1
  br label %while.body.2

while.body.2:                                     ; preds = %while.body.2.preheader, %while.body.2
  %len.163.2 = phi i32 [ %inc.2, %while.body.2 ], [ %inc4.1, %while.body.2.preheader ]
  %inc.2 = add nsw i32 %len.163.2, 1
  %scevgep6 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.163.2
  store i8 0, i8* %scevgep6, align 1, !tbaa !12
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
  %23 = mul i64 %div.2, 10
  %rem.2.decomposed = sub i64 %val.0.2.frozen, %23
  %conv3.2 = trunc i64 %rem.2.decomposed to i8
  %inc4.2 = add i32 %len.2.2, 1
  %scevgep5 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2.2
  store i8 %conv3.2, i8* %scevgep5, align 1, !tbaa !12
  %24 = icmp ult i64 %val.0.2, 10
  br i1 %24, label %do.end.2, label %do.body.2

do.end.2:                                         ; preds = %do.body.2
  %25 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not.2 = icmp eq i256 %25, 0
  %26 = add i32 %inc4.2, -1
  br i1 %cmp6.not.2, label %if.end22, label %for.cond.2

for.cond.2:                                       ; preds = %do.end.2
  %call.3 = call i32 @udivmod256(i256* nonnull %q, i256* nonnull %divisor, i256* nonnull %r, i256* nonnull %q) #18
  %27 = load i256, i256* %r, align 8, !tbaa !50
  %conv.3 = trunc i256 %27 to i64
  %cmp162.3 = icmp slt i32 %26, 56
  br i1 %cmp162.3, label %while.body.3.preheader, label %do.body.3.preheader

while.body.3.preheader:                           ; preds = %for.cond.2
  br label %while.body.3

while.body.3:                                     ; preds = %while.body.3.preheader, %while.body.3
  %len.163.3 = phi i32 [ %inc.3, %while.body.3 ], [ %inc4.2, %while.body.3.preheader ]
  %inc.3 = add nsw i32 %len.163.3, 1
  %scevgep4 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.163.3
  store i8 0, i8* %scevgep4, align 1, !tbaa !12
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
  %28 = mul i64 %div.3, 10
  %rem.3.decomposed = sub i64 %val.0.3.frozen, %28
  %conv3.3 = trunc i64 %rem.3.decomposed to i8
  %inc4.3 = add i32 %len.2.3, 1
  %scevgep3 = getelementptr [80 x i8], [80 x i8]* %buf, i32 0, i32 %len.2.3
  store i8 %conv3.3, i8* %scevgep3, align 1, !tbaa !12
  %29 = icmp ult i64 %val.0.3, 10
  br i1 %29, label %do.end.3, label %do.body.3

do.end.3:                                         ; preds = %do.body.3
  %30 = load i256, i256* %q, align 8, !tbaa !50
  %cmp6.not.3 = icmp eq i256 %30, 0
  br i1 %cmp6.not.3, label %if.end22, label %cleanup8
}

declare void @storageStore(i8*, i8*) #16

declare void @storageLoad(i8*, i8*) #16

declare i32 @getCallDataSize() #16

declare i32 @getReturnDataSize() #16

declare void @callDataCopy(i8*, i32, i32) #16

declare void @returnDataCopy(i8*, i32, i32) #16

declare i32 @call(i64, i8*, i8*, i8*, i32) #16

declare void @getCallValue(i8*) #16

declare void @getAddress(i8*) #16

declare void @getCaller(i8*) #16

declare void @getExternalBalance(i8*, i8*) #16

declare void @log(i8*, i32, i32, i8*, i8*, i8*, i8*) #16

; Function Attrs: noreturn
declare void @finish(i8*, i32) #17

; Function Attrs: noreturn
declare void @revert(i8*, i32) #17

define internal i32 @"PuppetPool::ReentrancyGuard::function::v_require__bool_string"(i1 %0, %struct.vector* %1) #16 {
entry:
  %uint328 = alloca i32, align 4
  %uint322 = alloca i32, align 4
  %uint32 = alloca i32, align 4
  br i1 %0, label %noassert, label %doassert

noassert:                                         ; preds = %entry
  ret i32 0

doassert:                                         ; preds = %entry
  %vector_len11 = bitcast %struct.vector* %1 to i32*
  %vector_is_null = icmp eq %struct.vector* %1, null
  %vector_len1 = load i32, i32* %vector_len11, align 4
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
  %vector_len412 = bitcast %struct.vector* %1 to i32*
  %vector_is_null5 = icmp eq %struct.vector* %1, null
  %vector_len6 = load i32, i32* %vector_len412, align 4
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

define internal i32 @"PuppetPool::Address::function::sendValue__address_uint256"([20 x i8] %0, i256 %1) #16 {
entry:
  %uint3232 = alloca i32, align 4
  %uint3226 = alloca i32, align 4
  %uint3224 = alloca i32, align 4
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
  %8 = call %struct.vector* @vector_new(i32 29, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([29 x i8], [29 x i8]* @const_string, i32 0, i32 0))
  %vector_len36 = bitcast %struct.vector* %8 to i32*
  %vector_is_null = icmp eq %struct.vector* %8, null
  %vector_len3 = load i32, i32* %vector_len36, align 4
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
  %vector_len637 = bitcast %struct.vector* %8 to i32*
  %vector_is_null7 = icmp eq %struct.vector* %8, null
  %vector_len8 = load i32, i32* %vector_len637, align 4
  %length9 = select i1 %vector_is_null7, i32 0, i32 %vector_len8
  store i32 %length9, i32* %uint3210, align 4
  %store11 = bitcast i32* %uint3210 to i8*
  call void @__leNtobe32(i8* %store11, i8* %15, i32 4)
  %17 = getelementptr i8, i8* %15, i32 32
  %data = getelementptr %struct.vector, %struct.vector* %8, i32 0, i32 2
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
  %24 = call %struct.vector* @vector_new(i32 58, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([58 x i8], [58 x i8]* @const_string.1, i32 0, i32 0))
  %vector_len2038 = bitcast %struct.vector* %24 to i32*
  %vector_is_null21 = icmp eq %struct.vector* %24, null
  %vector_len22 = load i32, i32* %vector_len2038, align 4
  %length23 = select i1 %vector_is_null21, i32 0, i32 %vector_len22
  %25 = add i32 %length23, 63
  %26 = and i32 %25, -32
  %27 = add i32 36, %26
  %28 = call i8* @__malloc(i32 %27)
  store i32 147028384, i32* %uint3224, align 4
  %store25 = bitcast i32* %uint3224 to i8*
  call void @__leNtobeN(i8* %store25, i8* %28, i32 4)
  %29 = getelementptr i8, i8* %28, i32 4
  %30 = udiv i32 %27, 8
  call void @__bzero8(i8* %29, i32 %30)
  %31 = getelementptr i8, i8* %29, i32 32
  store i32 32, i32* %uint3226, align 4
  %store27 = bitcast i32* %uint3226 to i8*
  call void @__leNtobe32(i8* %store27, i8* %29, i32 4)
  %32 = getelementptr i8, i8* %29, i32 32
  %vector_len2839 = bitcast %struct.vector* %24 to i32*
  %vector_is_null29 = icmp eq %struct.vector* %24, null
  %vector_len30 = load i32, i32* %vector_len2839, align 4
  %length31 = select i1 %vector_is_null29, i32 0, i32 %vector_len30
  store i32 %length31, i32* %uint3232, align 4
  %store33 = bitcast i32* %uint3232 to i8*
  call void @__leNtobe32(i8* %store33, i8* %31, i32 4)
  %33 = getelementptr i8, i8* %31, i32 32
  %data34 = getelementptr %struct.vector, %struct.vector* %24, i32 0, i32 2
  %data35 = bitcast [0 x i8]* %data34 to i8*
  call void @__memcpy(i8* %33, i8* %data35, i32 %length31)
  %34 = add i32 %length31, 31
  %35 = and i32 %34, -32
  %36 = getelementptr i8, i8* %33, i32 %35
  %37 = add i32 64, %35
  call void @revert(i8* %28, i32 %27)
  unreachable
}

define internal i32 @"PuppetPool::PuppetPool::function::deposits__address"([20 x i8] %0, i256* %1) #16 {
entry:
  %keccak_src = alloca i8, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)), align 1
  %elem3 = bitcast i8* %keccak_src to i8*
  %2 = bitcast i8* %elem3 to i256*
  store i256 1, i256* %2, align 8
  %elem1 = getelementptr i8, i8* %keccak_src, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32)
  %3 = bitcast i8* %elem1 to [20 x i8]*
  store [20 x i8] %0, [20 x i8]* %3, align 1
  %keccak_dst = alloca i256, align 8
  %balance = alloca i128, align 8
  store i128 0, i128* %balance, align 8
  %balance2 = bitcast i128* %balance to i8*
  %4 = call i32 @call(i64 9223372036854775807, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @keccak256_precompile.5, i32 0, i32 0), i8* %balance2, i8* %keccak_src, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)))
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

define internal i32 @"PuppetPool::PuppetPool::borrow__uint256::modifier0::nonReentrant"(i256 %0) #16 {
entry:
  %1 = alloca i256, align 8
  %slot.i18 = alloca i256, align 8
  %2 = bitcast i256* %slot.i18 to i8*
  %3 = alloca i256, align 8
  %slot.i17 = alloca i256, align 8
  %slot.i = alloca i256, align 8
  %buf.i = alloca i8, i32 32, align 1
  %4 = alloca i256, align 8
  %5 = bitcast i256* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %5)
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %2)
  store i256 0, i256* %1, align 8
  %6 = bitcast i256* %1 to i8*
  call void @storageLoad(i8* %6, i8* %2)
  %7 = bitcast i8* %2 to i256*
  %loaded_int.i = load i256, i256* %7, align 8
  store i256 %loaded_int.i, i256* %4, align 8
  %8 = bitcast i256* %1 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %8)
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %2)
  %success = icmp eq i32 0, 0
  br i1 %success, label %success1, label %bail

success1:                                         ; preds = %entry
  %9 = load i256, i256* %4, align 8
  %10 = alloca i1, align 1
  %11 = icmp eq i256 %9, 2
  %12 = icmp eq i1 %11, false
  store i1 %12, i1* %10, align 1
  %success2 = icmp eq i32 0, 0
  br i1 %success2, label %success3, label %bail4

bail:                                             ; preds = %entry
  ret i32 0

success3:                                         ; preds = %success1
  %13 = load i1, i1* %10, align 1
  %14 = call %struct.vector* @vector_new(i32 31, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @const_string.2, i32 0, i32 0))
  %15 = call i32 @"PuppetPool::ReentrancyGuard::function::v_require__bool_string"(i1 %13, %struct.vector* %14)
  %success5 = icmp eq i32 %15, 0
  br i1 %success5, label %success6, label %bail7

bail4:                                            ; preds = %success1
  ret i32 0

success6:                                         ; preds = %success3
  %16 = bitcast i256* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %16)
  %17 = bitcast i256* %slot.i18 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %17)
  store i256 0, i256* %slot.i18, align 8
  store i256 2, i256* %1, align 8
  %18 = bitcast i256* %slot.i18 to i8*
  %19 = bitcast i256* %1 to i8*
  call void @storageStore(i8* %18, i8* %19)
  %20 = bitcast i256* %1 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %20)
  %21 = bitcast i256* %slot.i18 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %21)
  %success8 = icmp eq i32 0, 0
  br i1 %success8, label %success9, label %bail10

bail7:                                            ; preds = %success3
  ret i32 %15

success9:                                         ; preds = %success6
  %22 = call i32 @"PuppetPool::PuppetPool::function::borrow__uint256"(i256 %0)
  %success11 = icmp eq i32 %22, 0
  br i1 %success11, label %success12, label %bail13

bail10:                                           ; preds = %success6
  ret i32 0

success12:                                        ; preds = %success9
  %23 = bitcast i256* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %23)
  %24 = bitcast i256* %slot.i18 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %24)
  store i256 0, i256* %slot.i18, align 8
  store i256 1, i256* %1, align 8
  %25 = bitcast i256* %slot.i18 to i8*
  %26 = bitcast i256* %1 to i8*
  call void @storageStore(i8* %25, i8* %26)
  %27 = bitcast i256* %1 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %27)
  %28 = bitcast i256* %slot.i18 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %28)
  %success14 = icmp eq i32 0, 0
  br i1 %success14, label %success15, label %bail16

bail13:                                           ; preds = %success9
  ret i32 %22

success15:                                        ; preds = %success12
  ret i32 0

bail16:                                           ; preds = %success12
  ret i32 0
}

define internal i32 @"PuppetPool::PuppetPool::function::calculateDepositRequired__uint256"(i256 %0, i256* %1) #16 {
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

define internal i32 @"PuppetPool::PuppetPool::function::_computeOraclePrice"(i256* %0) #16 {
entry:
  %stack.i = alloca i256, align 8
  %bytes4.i = alloca i32, align 4
  %address.i = alloca i8, i32 20, align 1
  %balance.i = alloca i128, align 8
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
  %9 = bitcast i256* %stack.i to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %9)
  %10 = bitcast i32* %bytes4.i to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %10)
  call void @llvm.lifetime.start.p0i8(i64 20, i8* %address.i)
  %11 = bitcast i128* %balance.i to i8*
  call void @llvm.lifetime.start.p0i8(i64 16, i8* %11)
  %12 = call i8* @__malloc(i32 add (i32 ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32), i32 36))
  %string.i = bitcast i8* %12 to %struct.vector*
  %data_len.i10 = bitcast %struct.vector* %string.i to i32*
  store i32 36, i32* %data_len.i10, align 4
  %data_size.i = getelementptr %struct.vector, %struct.vector* %string.i, i32 0, i32 1
  store i32 36, i32* %data_size.i, align 4
  %data.i = getelementptr %struct.vector, %struct.vector* %string.i, i32 0, i32 2
  %13 = bitcast [0 x i8]* %data.i to i8*
  store i32 1889567281, i32* %bytes4.i, align 4
  %store.i = bitcast i32* %bytes4.i to i8*
  call void @__leNtobeN(i8* %store.i, i8* %13, i32 4)
  %14 = getelementptr i8, i8* %13, i32 4
  call void @__bzero8(i8* %14, i32 4)
  %15 = getelementptr i8, i8* %14, i32 32
  %address_ptr.i = getelementptr i8, i8* %14, i32 12
  %address_ptr1.i = bitcast i8* %address_ptr.i to [20 x i8]*
  store [20 x i8] %loaded_address, [20 x i8]* %address_ptr1.i, align 1
  %16 = getelementptr i8, i8* %14, i32 32
  %address2.i = bitcast i8* %address.i to [20 x i8]*
  store [20 x i8] %loaded_address3, [20 x i8]* %address2.i, align 1
  %data3.i = getelementptr %struct.vector, %struct.vector* %string.i, i32 0, i32 2
  %data4.i = bitcast [0 x i8]* %data3.i to i8*
  %vector_len.i11 = bitcast %struct.vector* %string.i to i32*
  %vector_len5.i = load i32, i32* %vector_len.i11, align 4
  store i128 0, i128* %balance.i, align 8
  %value_transfer.i = bitcast i128* %balance.i to i8*
  %17 = call i32 @call(i64 9223372036854775807, i8* %address.i, i8* %value_transfer.i, i8* %data4.i, i32 %vector_len5.i)
  %success.i = icmp eq i32 %17, 0
  br i1 %success.i, label %success6.i, label %bail.i

success6.i:                                       ; preds = %entry
  %returndatasize.i = call i32 @getReturnDataSize()
  %size.i = add i32 %returndatasize.i, ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32)
  %18 = call i8* @__malloc(i32 %size.i)
  %string7.i = bitcast i8* %18 to %struct.vector*
  %data_len8.i12 = bitcast %struct.vector* %string7.i to i32*
  store i32 %returndatasize.i, i32* %data_len8.i12, align 4
  %data_size9.i = getelementptr %struct.vector, %struct.vector* %string7.i, i32 0, i32 1
  store i32 %returndatasize.i, i32* %data_size9.i, align 4
  %data10.i = getelementptr %struct.vector, %struct.vector* %string7.i, i32 0, i32 2
  %19 = bitcast [0 x i8]* %data10.i to i8*
  call void @returnDataCopy(i8* %19, i32 0, i32 %returndatasize.i)
  %data11.i = getelementptr %struct.vector, %struct.vector* %string7.i, i32 0, i32 2
  %vector_len13.i13 = bitcast %struct.vector* %string7.i to i32*
  %vector_len15.i = load i32, i32* %vector_len13.i13, align 4
  %data_length.i = zext i32 %vector_len15.i to i64
  %20 = icmp ule i64 32, %data_length.i
  br i1 %20, label %"PuppetPool::PuppetPool::function::v_call_IERC20_balanceOf__IERC20_address.exit", label %bail18.i

bail.i:                                           ; preds = %entry
  call void @revert(i8* null, i32 0)
  unreachable

bail18.i:                                         ; preds = %success6.i
  call void @revert(i8* null, i32 0)
  unreachable

"PuppetPool::PuppetPool::function::v_call_IERC20_balanceOf__IERC20_address.exit": ; preds = %success6.i
  %21 = bitcast [0 x i8]* %data11.i to i8*
  %22 = bitcast i256* %stack.i to i8*
  call void @__be32toleN(i8* %21, i8* %22, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int256.i = load i256, i256* %stack.i, align 8
  store i256 %abi_int256.i, i256* %8, align 8
  %23 = bitcast i256* %stack.i to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %23)
  %24 = bitcast i32* %bytes4.i to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %24)
  call void @llvm.lifetime.end.p0i8(i64 20, i8* %address.i)
  %25 = bitcast i128* %balance.i to i8*
  call void @llvm.lifetime.end.p0i8(i64 16, i8* %25)
  %success = icmp eq i32 0, 0
  br i1 %success, label %success4, label %bail

success4:                                         ; preds = %"PuppetPool::PuppetPool::function::v_call_IERC20_balanceOf__IERC20_address.exit"
  %26 = load i256, i256* %8, align 8
  %address = alloca [20 x i8], align 1
  store [20 x i8] %loaded_address, [20 x i8]* %address, align 1
  %balance = alloca i128, align 8
  %27 = bitcast [20 x i8]* %address to i8*
  %28 = bitcast i128* %balance to i8*
  call void @getExternalBalance(i8* %27, i8* %28)
  %balance5 = load i128, i128* %balance, align 8
  %29 = sext i128 %balance5 to i256
  store i256 %29, i256* %3, align 8
  store i256 1000000000000000000, i256* %2, align 8
  %left = bitcast i256* %3 to i32*
  %right = bitcast i256* %2 to i32*
  %output = bitcast i256* %1 to i32*
  call void @__mul32(i32* %left, i32* %right, i32* %output, i32 8)
  %mul = load i256, i256* %1, align 8
  store i256 %mul, i256* %dividend, align 8
  store i256 %26, i256* %divisor, align 8
  %udiv = call i32 @udivmod256(i256* %dividend, i256* %divisor, i256* %remainder, i256* %quotient)
  %success6 = icmp eq i32 %udiv, 0
  br i1 %success6, label %success7, label %bail8

bail:                                             ; preds = %"PuppetPool::PuppetPool::function::v_call_IERC20_balanceOf__IERC20_address.exit"
  ret i32 0

success7:                                         ; preds = %success4
  %quotient9 = load i256, i256* %quotient, align 8
  store i256 %quotient9, i256* %0, align 8
  ret i32 0

bail8:                                            ; preds = %success4
  call void @revert(i8* null, i32 0)
  unreachable
}

define internal i32 @"PuppetPool::PuppetPool::function::borrow__uint256"(i256 %0) #16 {
entry:
  %uint3291 = alloca i32, align 4
  %uint3285 = alloca i32, align 4
  %uint3283 = alloca i32, align 4
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
  %11 = call %struct.vector* @vector_new(i32 32, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([32 x i8], [32 x i8]* @const_string.3, i32 0, i32 0))
  %vector_len95 = bitcast %struct.vector* %11 to i32*
  %vector_is_null = icmp eq %struct.vector* %11, null
  %vector_len5 = load i32, i32* %vector_len95, align 4
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
  %vector_len896 = bitcast %struct.vector* %11 to i32*
  %vector_is_null9 = icmp eq %struct.vector* %11, null
  %vector_len10 = load i32, i32* %vector_len896, align 4
  %length11 = select i1 %vector_is_null9, i32 0, i32 %vector_len10
  store i32 %length11, i32* %uint3212, align 4
  %store13 = bitcast i32* %uint3212 to i8*
  call void @__leNtobe32(i8* %store13, i8* %18, i32 4)
  %20 = getelementptr i8, i8* %18, i32 32
  %data = getelementptr %struct.vector, %struct.vector* %11, i32 0, i32 2
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
  br i1 %success18, label %endif, label %bail20

endif:                                            ; preds = %then, %noassert
  %caller21 = alloca [20 x i8], align 1
  %30 = bitcast [20 x i8]* %caller21 to i8*
  call void @getCaller(i8* %30)
  %caller22 = load [20 x i8], [20 x i8]* %caller21, align 1
  %keccak_src = alloca i8, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)), align 1
  %elem97 = bitcast i8* %keccak_src to i8*
  %31 = bitcast i8* %elem97 to i256*
  store i256 1, i256* %31, align 8
  %elem23 = getelementptr i8, i8* %keccak_src, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32)
  %32 = bitcast i8* %elem23 to [20 x i8]*
  store [20 x i8] %caller22, [20 x i8]* %32, align 1
  %keccak_dst = alloca i256, align 8
  %balance = alloca i128, align 8
  store i128 0, i128* %balance, align 8
  %balance24 = bitcast i128* %balance to i8*
  %33 = call i32 @call(i64 9223372036854775807, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @keccak256_precompile.5, i32 0, i32 0), i8* %balance24, i8* %keccak_src, i32 add (i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32), i32 ptrtoint ([20 x i8]* getelementptr ([20 x i8], [20 x i8]* null, i32 1) to i32)))
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
  %elem2898 = bitcast i8* %keccak_src27 to i8*
  %38 = bitcast i8* %elem2898 to i256*
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
  %data_len99 = bitcast %struct.vector* %string to i32*
  store i32 68, i32* %data_len99, align 4
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
  %vector_len47100 = bitcast %struct.vector* %string to i32*
  %vector_is_null48 = icmp eq %struct.vector* %string, null
  %vector_len49 = load i32, i32* %vector_len47100, align 4
  %length50 = select i1 %vector_is_null48, i32 0, i32 %vector_len49
  %balance51 = alloca i128, align 8
  store i128 0, i128* %balance51, align 8
  %value_transfer = bitcast i128* %balance51 to i8*
  %52 = call i32 @call(i64 9223372036854775807, i8* %address, i8* %value_transfer, i8* %data46, i32 %length50)
  %success52 = icmp eq i32 %52, 0
  br i1 %success52, label %success53, label %bail54

bail20:                                           ; preds = %then
  ret i32 %29

success53:                                        ; preds = %endif
  %returndatasize = call i32 @getReturnDataSize()
  %size = add i32 %returndatasize, ptrtoint (%struct.vector* getelementptr (%struct.vector, %struct.vector* null, i32 1) to i32)
  %53 = call i8* @__malloc(i32 %size)
  %string55 = bitcast i8* %53 to %struct.vector*
  %data_len56101 = bitcast %struct.vector* %string55 to i32*
  store i32 %returndatasize, i32* %data_len56101, align 4
  %data_size57 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 1
  store i32 %returndatasize, i32* %data_size57, align 4
  %data58 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 2
  %54 = bitcast [0 x i8]* %data58 to i8*
  call void @returnDataCopy(i8* %54, i32 0, i32 %returndatasize)
  %data59 = getelementptr %struct.vector, %struct.vector* %string55, i32 0, i32 2
  %vector_len61102 = bitcast %struct.vector* %string55 to i32*
  %vector_is_null62 = icmp eq %struct.vector* %string55, null
  %vector_len63 = load i32, i32* %vector_len61102, align 4
  %length64 = select i1 %vector_is_null62, i32 0, i32 %vector_len63
  %data_length = zext i32 %length64 to i64
  %55 = icmp ule i64 32, %data_length
  br i1 %55, label %success65, label %bail66

bail54:                                           ; preds = %endif
  call void @revert(i8* null, i32 0)
  unreachable

success65:                                        ; preds = %success53
  %56 = bitcast [0 x i8]* %data59 to i8*
  %57 = bitcast i8* %56 to i8*
  %58 = bitcast i8* %57 to i64*
  %bool_ptr = getelementptr i64, i64* %58, i32 3
  %abi_bool = load i64, i64* %bool_ptr, align 8
  %bool = icmp ne i64 %abi_bool, 0
  br i1 %bool, label %noassert67, label %doassert68

bail66:                                           ; preds = %success53
  call void @revert(i8* null, i32 0)
  unreachable

noassert67:                                       ; preds = %success65
  %caller69 = alloca [20 x i8], align 1
  %59 = bitcast [20 x i8]* %caller69 to i8*
  call void @getCaller(i8* %59)
  %caller70 = load [20 x i8], [20 x i8]* %caller69, align 1
  %60 = call i8* @__malloc(i32 64)
  call void @__bzero8(i8* %60, i32 8)
  %61 = getelementptr i8, i8* %60, i32 64
  store i256 %4, i256* %uint25671, align 8
  %store72 = bitcast i256* %uint25671 to i8*
  call void @__leNtobe32(i8* %store72, i8* %60, i32 32)
  %62 = getelementptr i8, i8* %60, i32 32
  store i256 %0, i256* %uint25673, align 8
  %store74 = bitcast i256* %uint25673 to i8*
  call void @__leNtobe32(i8* %store74, i8* %62, i32 32)
  %63 = getelementptr i8, i8* %62, i32 32
  %64 = call i8* @__malloc(i32 64)
  call void @__bzero8(i8* %64, i32 8)
  %65 = getelementptr i8, i8* %64, i32 64
  store i256 -9537773560138156302262374008369018912504308177848412795308944527167260367056, i256* %bytes32, align 8
  %store75 = bitcast i256* %bytes32 to i8*
  call void @__leNtobeN(i8* %store75, i8* %64, i32 32)
  %66 = getelementptr i8, i8* %64, i32 32
  %address_ptr76 = getelementptr i8, i8* %66, i32 12
  %address_ptr77 = bitcast i8* %address_ptr76 to [20 x i8]*
  store [20 x i8] %caller70, [20 x i8]* %address_ptr77, align 1
  %67 = getelementptr i8, i8* %66, i32 32
  %next_topic = getelementptr i8, i8* %64, i32 32
  %next_topic78 = getelementptr i8, i8* %next_topic, i32 32
  call void @log(i8* %60, i32 64, i32 2, i8* %64, i8* %next_topic, i8* null, i8* null)
  ret i32 0

doassert68:                                       ; preds = %success65
  %68 = call %struct.vector* @vector_new(i32 15, i32 ptrtoint (i8* getelementptr (i8, i8* null, i32 1) to i32), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @const_string.6, i32 0, i32 0))
  %vector_len79103 = bitcast %struct.vector* %68 to i32*
  %vector_is_null80 = icmp eq %struct.vector* %68, null
  %vector_len81 = load i32, i32* %vector_len79103, align 4
  %length82 = select i1 %vector_is_null80, i32 0, i32 %vector_len81
  %69 = add i32 %length82, 63
  %70 = and i32 %69, -32
  %71 = add i32 36, %70
  %72 = call i8* @__malloc(i32 %71)
  store i32 147028384, i32* %uint3283, align 4
  %store84 = bitcast i32* %uint3283 to i8*
  call void @__leNtobeN(i8* %store84, i8* %72, i32 4)
  %73 = getelementptr i8, i8* %72, i32 4
  %74 = udiv i32 %71, 8
  call void @__bzero8(i8* %73, i32 %74)
  %75 = getelementptr i8, i8* %73, i32 32
  store i32 32, i32* %uint3285, align 4
  %store86 = bitcast i32* %uint3285 to i8*
  call void @__leNtobe32(i8* %store86, i8* %73, i32 4)
  %76 = getelementptr i8, i8* %73, i32 32
  %vector_len87104 = bitcast %struct.vector* %68 to i32*
  %vector_is_null88 = icmp eq %struct.vector* %68, null
  %vector_len89 = load i32, i32* %vector_len87104, align 4
  %length90 = select i1 %vector_is_null88, i32 0, i32 %vector_len89
  store i32 %length90, i32* %uint3291, align 4
  %store92 = bitcast i32* %uint3291 to i8*
  call void @__leNtobe32(i8* %store92, i8* %75, i32 4)
  %77 = getelementptr i8, i8* %75, i32 32
  %data93 = getelementptr %struct.vector, %struct.vector* %68, i32 0, i32 2
  %data94 = bitcast [0 x i8]* %data93 to i8*
  call void @__memcpy(i8* %77, i8* %data94, i32 %length90)
  %78 = add i32 %length90, 31
  %79 = and i32 %78, -32
  %80 = getelementptr i8, i8* %77, i32 %79
  %81 = add i32 64, %79
  call void @revert(i8* %72, i32 %71)
  unreachable
}

define void @main() #16 {
entry:
  %slot.i121 = alloca i256, align 8
  %buf.i122 = alloca i8, i32 32, align 1
  %0 = bitcast i8* %buf.i122 to i256*
  %slot.i119 = alloca i256, align 8
  %buf.i120 = alloca i8, i32 32, align 1
  %1 = alloca i256, align 8
  %slot.i118 = alloca i256, align 8
  %slot.i = alloca i256, align 8
  %buf.i = alloca i8, i32 32, align 1
  %2 = alloca i256, align 8
  %stack112 = alloca i256, align 8
  %stack98 = alloca i256, align 8
  %3 = alloca [20 x i8], align 1
  %4 = alloca [20 x i8], align 1
  %5 = alloca i256, align 8
  %stack48 = alloca i32, align 4
  %stack44 = alloca i32, align 4
  %6 = alloca i1, align 1
  %stack28 = alloca i256, align 8
  %stack24 = alloca i256, align 8
  %stack = alloca i256, align 8
  %7 = alloca i256, align 8
  call void @__init_heap()
  %calldatasize = call i32 @getCallDataSize()
  store i32 %calldatasize, i32* @calldata_len, align 4
  %8 = call i8* @__malloc(i32 %calldatasize)
  store i8* %8, i8** @calldata_data, align 4
  call void @callDataCopy(i8* %8, i32 0, i32 %calldatasize)
  %9 = icmp uge i32 %calldatasize, 4
  br i1 %9, label %switch, label %no_function_matched

no_function_matched:                              ; preds = %switch, %entry
  call void @revert(i8* null, i32 0)
  unreachable

switch:                                           ; preds = %entry
  %10 = bitcast i8* %8 to i32*
  %function_selector = load i32, i32* %10, align 4
  store i32 %function_selector, i32* @selector, align 4
  %argsdata = getelementptr i32, i32* %10, i32 1
  %argslen = sub i32 %calldatasize, 4
  switch i32 %function_selector, label %no_function_matched [
    i32 -585822675, label %11
    i32 -1202374961, label %20
    i32 -2104868861, label %32
    i32 1289552372, label %49
    i32 1831370492, label %68
    i32 461641416, label %77
    i32 1783893244, label %87
    i32 -320148539, label %97
    i32 676091324, label %103
  ]

11:                                               ; preds = %switch
  %value_transferred = alloca i128, align 8
  %12 = bitcast i128* %value_transferred to i8*
  call void @getCallValue(i8* %12)
  %value_transferred1 = load i128, i128* %value_transferred, align 8
  %is_value_transfer = icmp ne i128 %value_transferred1, 0
  br i1 %is_value_transfer, label %abort_value_transfer, label %not_value_transfer

not_value_transfer:                               ; preds = %11
  %data_length = zext i32 %argslen to i64
  %13 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %13)
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %buf.i122)
  store i256 0, i256* %slot.i121, align 8
  %14 = bitcast i256* %slot.i121 to i8*
  call void @storageLoad(i8* %14, i8* %buf.i122)
  %15 = bitcast i8* %buf.i122 to i256*
  %loaded_int.i = load i256, i256* %15, align 8
  store i256 %loaded_int.i, i256* %7, align 8
  %16 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %16)
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %buf.i122)
  %success = icmp eq i32 0, 0
  br i1 %success, label %success2, label %bail

abort_value_transfer:                             ; preds = %11
  call void @revert(i8* null, i32 0)
  unreachable

success2:                                         ; preds = %not_value_transfer
  %17 = call i8* @__malloc(i32 32)
  call void @__bzero8(i8* %17, i32 4)
  %18 = getelementptr i8, i8* %17, i32 32
  %arg8 = bitcast i256* %7 to i8*
  call void @__leNtobe32(i8* %arg8, i8* %17, i32 32)
  %19 = getelementptr i8, i8* %17, i32 32
  call void @finish(i8* %17, i32 32)
  unreachable

bail:                                             ; preds = %not_value_transfer
  call void @revert(i8* null, i32 0)
  unreachable

20:                                               ; preds = %switch
  %value_transferred3 = alloca i128, align 8
  %21 = bitcast i128* %value_transferred3 to i8*
  call void @getCallValue(i8* %21)
  %value_transferred4 = load i128, i128* %value_transferred3, align 8
  %is_value_transfer5 = icmp ne i128 %value_transferred4, 0
  br i1 %is_value_transfer5, label %abort_value_transfer7, label %not_value_transfer6

not_value_transfer6:                              ; preds = %20
  %data_length9 = zext i32 %argslen to i64
  %22 = icmp ule i64 32, %data_length9
  br i1 %22, label %success10, label %bail11

abort_value_transfer7:                            ; preds = %20
  call void @revert(i8* null, i32 0)
  unreachable

success10:                                        ; preds = %not_value_transfer6
  %23 = bitcast i32* %argsdata to i8*
  %24 = bitcast i8* %23 to i8*
  %25 = bitcast i256* %stack to i8*
  call void @__be32toleN(i8* %24, i8* %25, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int256 = load i256, i256* %stack, align 8
  %26 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %26)
  %27 = bitcast i256* %0 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %27)
  store i256 0, i256* %0, align 8
  store i256 %abi_int256, i256* %slot.i121, align 8
  %28 = bitcast i256* %0 to i8*
  %29 = bitcast i256* %slot.i121 to i8*
  call void @storageStore(i8* %28, i8* %29)
  %30 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %30)
  %31 = bitcast i256* %0 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %31)
  %success12 = icmp eq i32 0, 0
  br i1 %success12, label %success13, label %bail14

bail11:                                           ; preds = %not_value_transfer6
  call void @revert(i8* null, i32 0)
  unreachable

success13:                                        ; preds = %success10
  call void @finish(i8* null, i32 0)
  unreachable

bail14:                                           ; preds = %success10
  call void @revert(i8* null, i32 0)
  unreachable

32:                                               ; preds = %switch
  %value_transferred15 = alloca i128, align 8
  %33 = bitcast i128* %value_transferred15 to i8*
  call void @getCallValue(i8* %33)
  %value_transferred16 = load i128, i128* %value_transferred15, align 8
  %is_value_transfer17 = icmp ne i128 %value_transferred16, 0
  br i1 %is_value_transfer17, label %abort_value_transfer19, label %not_value_transfer18

not_value_transfer18:                             ; preds = %32
  %data_length21 = zext i32 %argslen to i64
  %34 = icmp ule i64 32, %data_length21
  br i1 %34, label %success22, label %bail23

abort_value_transfer19:                           ; preds = %32
  call void @revert(i8* null, i32 0)
  unreachable

success22:                                        ; preds = %not_value_transfer18
  %35 = bitcast i32* %argsdata to i8*
  %36 = bitcast i8* %35 to i8*
  %37 = bitcast i256* %stack24 to i8*
  call void @__be32toleN(i8* %36, i8* %37, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int25625 = load i256, i256* %stack24, align 8
  %38 = icmp ule i64 64, %data_length21
  br i1 %38, label %success26, label %bail27

bail23:                                           ; preds = %not_value_transfer18
  call void @revert(i8* null, i32 0)
  unreachable

success26:                                        ; preds = %success22
  %39 = bitcast i32* %argsdata to i8*
  %40 = getelementptr i8, i8* %39, i64 32
  %41 = bitcast i256* %stack28 to i8*
  call void @__be32toleN(i8* %40, i8* %41, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int25629 = load i256, i256* %stack28, align 8
  %42 = icmp eq i256 %abi_int25625, %abi_int25629
  %43 = icmp eq i1 %42, false
  store i1 %43, i1* %6, align 1
  %success30 = icmp eq i32 0, 0
  br i1 %success30, label %success31, label %bail32

bail27:                                           ; preds = %success22
  call void @revert(i8* null, i32 0)
  unreachable

success31:                                        ; preds = %success26
  %44 = call i8* @__malloc(i32 32)
  call void @__bzero8(i8* %44, i32 4)
  %45 = getelementptr i8, i8* %44, i32 32
  %46 = load i1, i1* %6, align 1
  %bool_val = select i1 %46, i8 1, i8 0
  %47 = getelementptr i8, i8* %44, i32 31
  store i8 %bool_val, i8* %47, align 1
  %48 = getelementptr i8, i8* %44, i32 32
  call void @finish(i8* %44, i32 32)
  unreachable

bail32:                                           ; preds = %success26
  call void @revert(i8* null, i32 0)
  unreachable

49:                                               ; preds = %switch
  %value_transferred33 = alloca i128, align 8
  %50 = bitcast i128* %value_transferred33 to i8*
  call void @getCallValue(i8* %50)
  %value_transferred34 = load i128, i128* %value_transferred33, align 8
  %is_value_transfer35 = icmp ne i128 %value_transferred34, 0
  br i1 %is_value_transfer35, label %abort_value_transfer37, label %not_value_transfer36

not_value_transfer36:                             ; preds = %49
  %data_length39 = zext i32 %argslen to i64
  %51 = icmp ule i64 32, %data_length39
  br i1 %51, label %success40, label %bail41

abort_value_transfer37:                           ; preds = %49
  call void @revert(i8* null, i32 0)
  unreachable

success40:                                        ; preds = %not_value_transfer36
  %52 = bitcast i32* %argsdata to i8*
  %53 = bitcast i8* %52 to i8*
  %54 = bitcast i8* %53 to i64*
  %bool_ptr = getelementptr i64, i64* %54, i32 3
  %abi_bool = load i64, i64* %bool_ptr, align 8
  %55 = icmp ule i64 64, %data_length39
  br i1 %55, label %success42, label %bail43

bail41:                                           ; preds = %not_value_transfer36
  call void @revert(i8* null, i32 0)
  unreachable

success42:                                        ; preds = %success40
  %56 = bitcast i32* %argsdata to i8*
  %57 = getelementptr i8, i8* %56, i64 32
  %58 = bitcast i32* %stack44 to i8*
  call void @__be32toleN(i8* %57, i8* %58, i32 ptrtoint (i32* getelementptr (i32, i32* null, i32 1) to i32))
  %abi_int32 = load i32, i32* %stack44, align 4
  %data_offset = zext i32 %abi_int32 to i64
  %data_offset45 = add i64 %data_offset, 0
  %next_offset = add i64 %data_offset45, 32
  %59 = icmp ule i64 %next_offset, %data_length39
  br i1 %59, label %success46, label %bail47

bail43:                                           ; preds = %success40
  call void @revert(i8* null, i32 0)
  unreachable

success46:                                        ; preds = %success42
  %60 = bitcast i32* %argsdata to i8*
  %61 = getelementptr i8, i8* %60, i64 %data_offset45
  %62 = bitcast i32* %stack48 to i8*
  call void @__be32toleN(i8* %61, i8* %62, i32 ptrtoint (i32* getelementptr (i32, i32* null, i32 1) to i32))
  %abi_int3249 = load i32, i32* %stack48, align 4
  %string_len = zext i32 %abi_int3249 to i64
  %stringend = add i64 %next_offset, %string_len
  %63 = icmp ule i64 %stringend, %data_length39
  br i1 %63, label %success50, label %bail51

bail47:                                           ; preds = %success42
  call void @revert(i8* null, i32 0)
  unreachable

success50:                                        ; preds = %success46
  %64 = icmp ne i64 %abi_bool, 0
  %65 = bitcast i32* %argsdata to i8*
  %string_start = getelementptr i8, i8* %65, i64 %next_offset
  %string_len52 = trunc i64 %string_len to i32
  %66 = call %struct.vector* @vector_new(i32 %string_len52, i32 1, i8* %string_start)
  %67 = call i32 @"PuppetPool::ReentrancyGuard::function::v_require__bool_string"(i1 %64, %struct.vector* %66)
  %success53 = icmp eq i32 %67, 0
  br i1 %success53, label %success54, label %bail55

bail51:                                           ; preds = %success46
  call void @revert(i8* null, i32 0)
  unreachable

success54:                                        ; preds = %success50
  call void @finish(i8* null, i32 0)
  unreachable

bail55:                                           ; preds = %success50
  call void @revert(i8* null, i32 0)
  unreachable

68:                                               ; preds = %switch
  %value_transferred56 = alloca i128, align 8
  %69 = bitcast i128* %value_transferred56 to i8*
  call void @getCallValue(i8* %69)
  %value_transferred57 = load i128, i128* %value_transferred56, align 8
  %is_value_transfer58 = icmp ne i128 %value_transferred57, 0
  br i1 %is_value_transfer58, label %abort_value_transfer60, label %not_value_transfer59

not_value_transfer59:                             ; preds = %68
  %data_length62 = zext i32 %argslen to i64
  %70 = icmp ule i64 32, %data_length62
  br i1 %70, label %success63, label %bail64

abort_value_transfer60:                           ; preds = %68
  call void @revert(i8* null, i32 0)
  unreachable

success63:                                        ; preds = %not_value_transfer59
  %71 = bitcast i32* %argsdata to i8*
  %72 = bitcast i8* %71 to i8*
  %address_ptr = getelementptr i8, i8* %72, i32 12
  %address_ptr65 = bitcast i8* %address_ptr to [20 x i8]*
  %address = load [20 x i8], [20 x i8]* %address_ptr65, align 1
  %73 = call i32 @"PuppetPool::PuppetPool::function::deposits__address"([20 x i8] %address, i256* %5)
  %success66 = icmp eq i32 %73, 0
  br i1 %success66, label %success67, label %bail68

bail64:                                           ; preds = %not_value_transfer59
  call void @revert(i8* null, i32 0)
  unreachable

success67:                                        ; preds = %success63
  %74 = call i8* @__malloc(i32 32)
  call void @__bzero8(i8* %74, i32 4)
  %75 = getelementptr i8, i8* %74, i32 32
  %arg869 = bitcast i256* %5 to i8*
  call void @__leNtobe32(i8* %arg869, i8* %74, i32 32)
  %76 = getelementptr i8, i8* %74, i32 32
  call void @finish(i8* %74, i32 32)
  unreachable

bail68:                                           ; preds = %success63
  call void @revert(i8* null, i32 0)
  unreachable

77:                                               ; preds = %switch
  %value_transferred70 = alloca i128, align 8
  %78 = bitcast i128* %value_transferred70 to i8*
  call void @getCallValue(i8* %78)
  %value_transferred71 = load i128, i128* %value_transferred70, align 8
  %is_value_transfer72 = icmp ne i128 %value_transferred71, 0
  br i1 %is_value_transfer72, label %abort_value_transfer74, label %not_value_transfer73

not_value_transfer73:                             ; preds = %77
  %data_length76 = zext i32 %argslen to i64
  %79 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %79)
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %buf.i122)
  store i256 2, i256* %slot.i121, align 8
  %80 = bitcast i256* %slot.i121 to i8*
  call void @storageLoad(i8* %80, i8* %buf.i122)
  %81 = bitcast i8* %buf.i122 to [20 x i8]*
  %loaded_address.i = load [20 x i8], [20 x i8]* %81, align 1
  store [20 x i8] %loaded_address.i, [20 x i8]* %4, align 1
  %82 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %82)
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %buf.i122)
  %success77 = icmp eq i32 0, 0
  br i1 %success77, label %success78, label %bail79

abort_value_transfer74:                           ; preds = %77
  call void @revert(i8* null, i32 0)
  unreachable

success78:                                        ; preds = %not_value_transfer73
  %83 = call i8* @__malloc(i32 32)
  call void @__bzero8(i8* %83, i32 4)
  %84 = getelementptr i8, i8* %83, i32 32
  %85 = load [20 x i8], [20 x i8]* %4, align 1
  %address_ptr80 = getelementptr i8, i8* %83, i32 12
  %address_ptr81 = bitcast i8* %address_ptr80 to [20 x i8]*
  store [20 x i8] %85, [20 x i8]* %address_ptr81, align 1
  %86 = getelementptr i8, i8* %83, i32 32
  call void @finish(i8* %83, i32 32)
  unreachable

bail79:                                           ; preds = %not_value_transfer73
  call void @revert(i8* null, i32 0)
  unreachable

87:                                               ; preds = %switch
  %value_transferred82 = alloca i128, align 8
  %88 = bitcast i128* %value_transferred82 to i8*
  call void @getCallValue(i8* %88)
  %value_transferred83 = load i128, i128* %value_transferred82, align 8
  %is_value_transfer84 = icmp ne i128 %value_transferred83, 0
  br i1 %is_value_transfer84, label %abort_value_transfer86, label %not_value_transfer85

not_value_transfer85:                             ; preds = %87
  %data_length88 = zext i32 %argslen to i64
  %89 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %89)
  call void @llvm.lifetime.start.p0i8(i64 32, i8* %buf.i122)
  store i256 3, i256* %slot.i121, align 8
  %90 = bitcast i256* %slot.i121 to i8*
  call void @storageLoad(i8* %90, i8* %buf.i122)
  %91 = bitcast i8* %buf.i122 to [20 x i8]*
  %loaded_address.i123 = load [20 x i8], [20 x i8]* %91, align 1
  store [20 x i8] %loaded_address.i123, [20 x i8]* %3, align 1
  %92 = bitcast i256* %slot.i121 to i8*
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %92)
  call void @llvm.lifetime.end.p0i8(i64 32, i8* %buf.i122)
  %success89 = icmp eq i32 0, 0
  br i1 %success89, label %success90, label %bail91

abort_value_transfer86:                           ; preds = %87
  call void @revert(i8* null, i32 0)
  unreachable

success90:                                        ; preds = %not_value_transfer85
  %93 = call i8* @__malloc(i32 32)
  call void @__bzero8(i8* %93, i32 4)
  %94 = getelementptr i8, i8* %93, i32 32
  %95 = load [20 x i8], [20 x i8]* %3, align 1
  %address_ptr92 = getelementptr i8, i8* %93, i32 12
  %address_ptr93 = bitcast i8* %address_ptr92 to [20 x i8]*
  store [20 x i8] %95, [20 x i8]* %address_ptr93, align 1
  %96 = getelementptr i8, i8* %93, i32 32
  call void @finish(i8* %93, i32 32)
  unreachable

bail91:                                           ; preds = %not_value_transfer85
  call void @revert(i8* null, i32 0)
  unreachable

97:                                               ; preds = %switch
  %data_length95 = zext i32 %argslen to i64
  %98 = icmp ule i64 32, %data_length95
  br i1 %98, label %success96, label %bail97

success96:                                        ; preds = %97
  %99 = bitcast i32* %argsdata to i8*
  %100 = bitcast i8* %99 to i8*
  %101 = bitcast i256* %stack98 to i8*
  call void @__be32toleN(i8* %100, i8* %101, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int25699 = load i256, i256* %stack98, align 8
  %102 = call i32 @"PuppetPool::PuppetPool::borrow__uint256::modifier0::nonReentrant"(i256 %abi_int25699)
  %success100 = icmp eq i32 %102, 0
  br i1 %success100, label %success101, label %bail102

bail97:                                           ; preds = %97
  call void @revert(i8* null, i32 0)
  unreachable

success101:                                       ; preds = %success96
  call void @finish(i8* null, i32 0)
  unreachable

bail102:                                          ; preds = %success96
  call void @revert(i8* null, i32 0)
  unreachable

103:                                              ; preds = %switch
  %value_transferred103 = alloca i128, align 8
  %104 = bitcast i128* %value_transferred103 to i8*
  call void @getCallValue(i8* %104)
  %value_transferred104 = load i128, i128* %value_transferred103, align 8
  %is_value_transfer105 = icmp ne i128 %value_transferred104, 0
  br i1 %is_value_transfer105, label %abort_value_transfer107, label %not_value_transfer106

not_value_transfer106:                            ; preds = %103
  %data_length109 = zext i32 %argslen to i64
  %105 = icmp ule i64 32, %data_length109
  br i1 %105, label %success110, label %bail111

abort_value_transfer107:                          ; preds = %103
  call void @revert(i8* null, i32 0)
  unreachable

success110:                                       ; preds = %not_value_transfer106
  %106 = bitcast i32* %argsdata to i8*
  %107 = bitcast i8* %106 to i8*
  %108 = bitcast i256* %stack112 to i8*
  call void @__be32toleN(i8* %107, i8* %108, i32 ptrtoint (i256* getelementptr (i256, i256* null, i32 1) to i32))
  %abi_int256113 = load i256, i256* %stack112, align 8
  %109 = call i32 @"PuppetPool::PuppetPool::function::calculateDepositRequired__uint256"(i256 %abi_int256113, i256* %2)
  %success114 = icmp eq i32 %109, 0
  br i1 %success114, label %success115, label %bail116

bail111:                                          ; preds = %not_value_transfer106
  call void @revert(i8* null, i32 0)
  unreachable

success115:                                       ; preds = %success110
  %110 = call i8* @__malloc(i32 32)
  call void @__bzero8(i8* %110, i32 4)
  %111 = getelementptr i8, i8* %110, i32 32
  %arg8117 = bitcast i256* %2 to i8*
  call void @__leNtobe32(i8* %arg8117, i8* %110, i32 32)
  %112 = getelementptr i8, i8* %110, i32 32
  call void @finish(i8* %110, i32 32)
  unreachable

bail116:                                          ; preds = %success110
  call void @revert(i8* null, i32 0)
  unreachable
}

attributes #0 = { nofree norecurse nosync nounwind writeonly "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" }
attributes #1 = { nofree norecurse nosync nounwind "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" }
attributes #2 = { nofree norecurse nosync nounwind readonly "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" }
attributes #3 = { nounwind "frame-pointer"="none" "min-legal-vector-width"="0" "no-builtins" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" }
attributes #4 = { noinline nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { inaccessiblememonly nofree nosync nounwind willreturn "target-features" }
attributes #6 = { nofree nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly "target-features" }
attributes #8 = { nofree noinline norecurse nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #10 = { nofree nosync nounwind readnone speculatable willreturn "target-features" }
attributes #11 = { norecurse nounwind readnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #12 = { nofree norecurse nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #13 = { norecurse nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #14 = { nounwind writeonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #15 = { argmemonly nofree nosync nounwind willreturn "target-features" }
attributes #16 = { "target-features" }
attributes #17 = { noreturn "target-features" }
attributes #18 = { nobuiltin nounwind "no-builtins" }
attributes #19 = { nobuiltin "no-builtins" }
attributes #20 = { nounwind }

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
