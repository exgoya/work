[wiki:goya wiki_goya]

-ager thread pstack {{{ while true; do ps -ef|grep $USER|grep
gmaster|grep -v grep|awk ‘{print $2}’\|xargs pstack|grep ‘Thread 6’\|awk
‘{print $6}’\|grep -o ’[0-9]\*’\|xargs pstack; usleep 500; done }}}

{{{ while true ; do date ps -eo pid,wchan=WIDE-WCHAN-COLUMN,s,cmd \|grep
” D” ; sleep 0.5; done }}}

| {{{ ps -eo user,ppid,rss,size,vsize,pmem,pcpu,time,cmd —sort -rss|grep
  sunje|awk ‘{sum += $4} END { print sum }’ }}} {{{ cat out.txt \|awk
  ‘{sum+=$17} END{print sum;}’ }}} {{{ while :; do ps aux \|grep -v grep
  \| grep pdbTest \| awk ’ { printf “%s %s”,strftime(“%Y%m%d%H%M%S”),$0
  } ’; sleep 1; done
| }}} {{{

[goya@tech10 log]$ grep -A4 COMMIT g2n1.log > g2n1_commit.log
[goya@tech10 log]$ grep -A4 COMMIT g2n2.log > g2n2_commit.log

[goya@tech10 log]$ grep -B1 “^--” g2n1_commit.log \|grep -v “--”\|awk ‘{
print $1}' \|sort -u 0000000000000000 [goya@tech10 log]$ grep -B1 “^--”
g2n2_commit.log \|grep -v “--”\|awk’{ print $1}’ \|sort -u
0000000000000000 }}}

redolog size sorting {{{

$ ./gdump LOG redo_0_0_g2n1.log –number 1702028941 –fetch 10000 >
10000a.log

$ grep -e “[LOG” a.log > b.log

$ awk ‘{print $6}’ b.log > c.log

$ sed ‘s/[^0-9]//g’ c.log \|sort -n > d.log

[goya@tech10 tmp]$ sort b.log -t ‘(’ -k4nr \|head [LOG #82] :
BLOCK(982482), LSN(1702029023), SIZE(2452), PIECE_COUNT(8),
TRANS_ID(F6C4004D0311), TRANS_SEQ(8035295), RID(0,0,43890) [LOG #58] :
BLOCK(982453), LSN(1702028999), SIZE(2446), PIECE_COUNT(8),
TRANS_ID(FC3E003703A0), TRANS_SEQ(7867468), RID(0,0,43890) [LOG #13] :
BLOCK(982411), LSN(1702028954), SIZE(2258), PIECE_COUNT(6),
TRANS_ID(FC3E003003A0), TRANS_SEQ(7867467), RID(0,0,43890) [LOG #14] :
BLOCK(982416), LSN(1702028955), SIZE(2242), PIECE_COUNT(5),
TRANS_ID(F6FF003B025F), TRANS_SEQ(7944604), RID(0,0,43890) [LOG #19] :
BLOCK(982427), LSN(1702028960), SIZE(2242), PIECE_COUNT(5),
TRANS_ID(F6C400450311), TRANS_SEQ(8035294), RID(0,0,43890) [LOG #11] :
BLOCK(982404), LSN(1702028952), SIZE(2240), PIECE_COUNT(5),
TRANS_ID(3736002901C9), TRANS_SEQ(8227165), RID(0,0,43890) [LOG #92] :
BLOCK(982491), LSN(1702029033), SIZE(2240), PIECE_COUNT(5),
TRANS_ID(FC3F000C03A0), TRANS_SEQ(7867470), RID(0,0,43890) [LOG #65] :
BLOCK(982462), LSN(1702029006), SIZE(2238), PIECE_COUNT(5),
TRANS_ID(FC3F000503A0), TRANS_SEQ(7867469), RID(0,0,43890) [LOG #47] :
BLOCK(982446), LSN(1702028988), SIZE(1483), PIECE_COUNT(6),
TRANS_ID(3736003501C9), TRANS_SEQ(8227167), RID(0,0,43890) [LOG #95] :
BLOCK(982498), LSN(1702029036), SIZE(1483), PIECE_COUNT(6),
TRANS_ID(5A5F002F0225), TRANS_SEQ(7955716), RID(0,0,43890)

[goya@tech10 tmp]$ grep -e “[PIECE” a.log \|grep -v COMMIT|sort -t ‘(’
-k3nr \|head -20 [PIECE #3] : TYPE(HEAP_INSERT), SIZE(1139),
CLASS(TABLE), REDO_TYPE(PAGE), PROPAGATE_LOG(YES), RID(2,6,4613384),
SEGMENT_PHYSICAL_ID(188506114621440) [PIECE #5] : TYPE(HEAP_INSERT),
SIZE(1139), CLASS(TABLE), REDO_TYPE(PAGE), PROPAGATE_LOG(YES),
RID(2,0,4636546), SEGMENT_PHYSICAL_ID(188506114621440) [PIECE #5] :
TYPE(HEAP_INSERT), SIZE(1139), CLASS(TABLE), REDO_TYPE(PAGE),
PROPAGATE_LOG(YES), RID(2,0,4658966),
SEGMENT_PHYSICAL_ID(188506114621440) [PIECE #2] : TYPE(HEAP_INSERT),
SIZE(1138), CLASS(TABLE), REDO_TYPE(PAGE), PROPAGATE_LOG(YES),
RID(2,1,4568752), SEGMENT_PHYSICAL_ID(188506114621440) [PIECE #5] :
TYPE(HEAP_INSERT), SIZE(1138), CLASS(TABLE), REDO_TYPE(PAGE),
PROPAGATE_LOG(YES), RID(2,0,4650640),
SEGMENT_PHYSICAL_ID(188506114621440) [PIECE #3] :
TYPE(INSERT_UNDO_RECORD), SIZE(956), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,60,63231) [PIECE #3] :
TYPE(INSERT_UNDO_RECORD), SIZE(956), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,70,63172) [PIECE #6] :
TYPE(INSERT_UNDO_RECORD), SIZE(956), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,0,63173) [PIECE #3] :
TYPE(INSERT_UNDO_RECORD), SIZE(955), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,13,64575) [PIECE #3] :
TYPE(INSERT_UNDO_RECORD), SIZE(955), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,42,14134) [PIECE #3] :
TYPE(INSERT_UNDO_RECORD), SIZE(954), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,6,64575) [PIECE #4] :
TYPE(INSERT_UNDO_RECORD), SIZE(954), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,49,64574) [PIECE #6] :
TYPE(INSERT_UNDO_RECORD), SIZE(953), CLASS(TRANSACTION),
REDO_TYPE(UNDO), PROPAGATE_LOG(YES), RID(1,0,64575) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(945), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,0,4603032) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(945), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,0,4627526) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(945), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,1,4632369) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(944), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,0,4560235) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(944), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,0,4576780) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(943), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,2,4621872) [PIECE #0] :
TYPE(SML_SUPPL_LOG_UPDATE_BEFORE_COLS), SIZE(943), CLASS(EXTERNAL),
REDO_TYPE(NONE), PROPAGATE_LOG(YES), RID(2,4,4589755) }}}
