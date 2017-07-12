program draw_ctrl;
 uses crt,graph,init;
  label 10,20,15;
  Const  bk_colr:integer=15007;
  const   now_color:integer=11111;
  const  again:boolean=false;
  type t=record
         x,y,l:integer;
         m,n:array [1..3]of integer;
         nu :shortint;
        end;
  var   cir,linee,savee,hu,savdot:t;
        movespeed:char;

        qq,ww:integer;
        nowchar, ch, ch1, flna :char;
        aa,bb:array[1..3]of integer;
        b,drawb:boolean;
        f:file of shortint;
        trb:boolean;
        p:pointer;
        ftox:file of char;
   procedure set_back(o:shortint);
     begin
       if o=1 then  bk_colr:=bk_colr+1;
       if o=-1 then bk_colr:=bk_colr-1;
       setbkcolor(bk_colr mod 16);
     end;
   procedure dohu;
    var r,x,y,th:integer;
        rou,thjh:real;
    begin
       hu.nu:=hu.nu+1;   hu.m[hu.nu]:=qq;   hu.n[hu.nu]:=ww;
       if hu.nu>=2 then begin
                        r:=round(sqrt(sqr(hu.m[1]-hu.m[2])+sqr(hu.n[1]-hu.n[2]))) div 2;
                        for th:=1 to 360 do begin
                            thjh:=th*pi/180;
                            rou:=r*cos(thjh);
                            x:=round(rou*cos(thjh));
                            y:=round(rou*sin(thjh));
                            x:=x-r; y:=y-r;           hu.nu:=0;
                            putpixel(x,y,getcolor);
                            if keypressed then if readkey='c' then exit;
                            end;{for}
                        end;{if}
       end;{p.}
 procedure beep(i:integer);
       begin
         sound(2221);
         delay(150);
         nosound;
       end;
  procedure soundd(i:byte);
      var hz:integer;
       begin
        if i=1 then for hz:=4     to 11 do beep(hz*186);
        if i=0 then for hz:=11 downto 4 do beep(hz*178);
       end;
  procedure readkeybd (var c:char;var b:boolean);
       begin {$i-}
          read(ftox,c);
          if ioresult<>0 then begin
                                c:=#27;
                                exit;
                               end;
          if c<> #0 then b:=false
                else
                  begin
                    b:=true;
                    read(ftox,c);
                    if ioresult<>0 then begin
                              c:=#27;
                              exit;
                             end;
                  end;
            {$i+}
       end;

     procedure showAgain(x,y:integer);
      label 1;
     var w,v:integer;u:shortint; ch:char;b:boolean; p:integer;
     begin
           p:=getcolor;
           setcolor(yellow);
           outtextxy(1,1,'Please input your picture file''s name(a..z) :');
           readkeybd(ch,b);
           outtextxy(370,1,ch );  delay (400);
           {$i-}
          assign(f,ch); v:=x;w:=y;
          reset(f);
          if ioresult<>0 then
              begin beep(2888);soundd(0);
               setcolor(getbkcolor);
               outtextxy(1,1,'Please input your picture file''s name(a..z) :');
               outtextxy(370,1,ch);
               setcolor(p);
               exit;
              end;
          {i+}
          setcolor(getbkcolor);
           outtextxy(1,1,'Please input your picture file''s name(a..z) :');
           outtextxy(370,1,ch);
           setcolor(p);
       While not eof(f) do
        Begin
         read(f,u);
         if keypressed then if readkey='p' then goto 1;
         if u>=0 then begin
                     w:=w+1;
                     putpixel(v,w,u);
                     end
                     else begin v:=v+1; w:=y;end;
        End;
      1: beep(1000);
       putpixel(v,w,getbkcolor);
       close(f);
      end;


    procedure dosave;
    var bb:boolean;   xxx,yyy:integer;  xx,zzz:shortint;
      begin
        bb:=false;
        with savee do
          begin
            nu:=nu+1;
            m[nu]:=qq;
            n[nu]:=ww;
            if nu=2 then
                begin
                  flna:=succ('z');
                  nu:=0;
                  while(not bb) and( flna<>pred('a')) do
                    begin
                     flna:=pred(flna);
                     assign(f,flna);
                     {$i-}
                     reset(f);
                     bb:=ioresult=0;
                     {$i+}
                    end;
                    if flna<>pred('a') then close(f);
                  flna:=succ(flna);
                 assign(f,flna);
                 rewrite(f);
                  for xxx:=m[1]    to m[2]-1 do
                   Begin
                      for yyy:=n[1]     to n[2]-1 do
                       begin
                          zzz:=getpixel(xxx,yyy);
                          write(f,zzz);
                       end;
                       xx:=-100;
                     write(f,xx);
                   End;
                  close(f);
                  beep(1664);
                end;{end of if}
            end{ of with};
        end;{of procedure}

  procedure docircle;
      var r:integer;l:real;           co:integer;
          o,p:real;
       begin                     {507}
         with cir do
          begin
            nu:=nu+1    ;
            co:=getcolor;
            m[nu]:=qq  ;
            n[nu]:=ww  ;
          end;
            If cir.nu>=2 then
              begin
                o:=cir.m[2]-cir.m[1];    setcolor(getbkcolor);outtextxy(507,1,'circle');
                p:=cir.n[2]-cir.n[1];    setcolor(co);
                l:=sqrt(sqr(o)+sqr(p));
                r:=trunc(l);
                graph.circle(cir.m[1],cir.n[1], r);
                cir.nu:=0;  beep(3100);
              end else
                     begin
                        setcolor(yellow);
                        outtextxy(507,1,'circle');
                        setcolor(co);
                     end;
      end;
  procedure doline;
      var co:integer;
      begin                  {457,1)}
      with linee do
        begin
          nu:=nu+1;        co:=getcolor;if nu=1 then begin  setcolor(yellow);outtextxy(457,1,'line');end;
          m[nu]:=qq  ;         if nu=2 then   begin  setcolor(getbkcolor);outtextxy(457,1,'line');end;
          n[nu]:=ww;          setcolor(co);
          if nu=2 then
            begin
              line(m[1],n[1],m[2],n[2]);
              nu:=0;  beep(3100);
            end;
        end;
      end;
  procedure quitt;
    var co:integer;
          procedure q1 (var q2:t);
              begin
               q2.nu:=0;
              end;
      begin
         q1(cir);q1(savee);q1(linee); q1(hu);
         co:=getcolor;
         setcolor(getbkcolor);
         outtextxy(457,1,'line');
         outtextxy(507,1,'circle');
         setcolor(co);
      end;
  procedure mmove(c:char);
    var sp:integer  ;   co:shortint;  s1,s2,s3,sl:string;
    begin
     if c='s' then sp:=1;
     if c='f' then sp:=23;
     if not trb then  putpixel(qq,ww,getbkcolor);      {should check before put...}
      case ch of
       #75:qq:=qq-sp;
       #77:qq:=qq+sp;
       #72:ww:=ww-sp;
       #80:ww:=ww+sp;
      end;
      co:=getcolor;
      if qq<1 then qq:=qq+sp;
      if qq>getmaxx-1 then qq:=qq-sp;
      if ww>getmaxy-1 then ww:=ww-sp;
      if ww<10 then ww:=ww+sp;
      str(qq,s1);str(ww ,s2);
      s3:=concat(s1,',',s2);
      setcolor(getbkcolor);  outtextxy(582,470,sl);
      setcolor(14);outtextxy(582,470,s3);
      setcolor(co);
      sl:=s3;
      if not trb then putpixel(qq,ww,white+blink) else putpixel(qq,ww,getcolor);              {}
    end;
  procedure set1(o:integer);
    begin
      if o=1 then now_color:=now_color+1;
      if o=-1 then now_color:=now_color-1;
      setcolor(now_color mod 16);
      outtextxy(574,1,'NowColor');
    end;
  procedure doSetColor(o:integer);
    begin
      { case ch of
       '~':set1(0); '!':set1(1);'@':set1(2);'#':set1(3);
        '$':set1(4);'%':set1(5);'^':set1(6);
        '&':set1(7);'*':set1(8);'(':set1(9);
        ')':set1(10);'Q':SET1(11);'W':SET1(12);
        'E':SET1(13);'R':SET1(14);'T':SET1(15);
        End;
         beep(2000); }   set1(o);
    end;
  procedure showHelp;
    var
       co:integer;st:array [1..15] of string;r:integer;
       size:word;
     begin
       size:=imagesize(0,0,getmaxx,getmaxy);
       getmem(p,size);
       getImage(0,0,getmaxx,getmaxy,p^);
          st[1]:='Welcome!' ;
          st[2]:='   "f": draw lines;   "r": draw circles;';
          st[3]:='   "a": jump with long step;'             ;
          st[4]:='   "z": move step by step;'                ;
          st[5]:='   "q": programme reset;'                   ;
          st[6]:='   "w": clear screen;   '                    ;
          st[7]:='   "e": move with trance after you;'          ;
          st[8]:='   "s": save the picture .'                    ;
          st[9]:='         you must point out the left-up point and';
          st[10]:='         the right-down point first.'             ;
          st[11]:='   "x": show a piece of picture you''ve saved.'    ;
          st[12]:='   "["or"{": change the color of your pen.'              ;
          st[13]:='   "]"or"}": change the color of your paper.'             ;
          st[14]:='                                        '             ;
          st[15]:='      .............press any key................. '    ;

          co:=getcolor;
          setcolor(yellow);
          for r:=1 to 15 do
            begin
               outtextxy(33,33+r*10,st[r]);
            end;
          setcolor(co);
          repeat until keypressed;
          beep(2222);
          cleardevice;
          putimage(0,0,p^,xorput);
     end;

  procedure kuang;
    var x,y:integer;
    begin
      for x:= 0 to getmaxx do
        begin   putpixel(x,0,red);putpixel(x,9,red);putpixel(x,getmaxy,red);end;
     for y:=0 to getmaxy do
       begin putpixel(0,y,red);putpixel(getmaxx,y,red); end;
    end;
begin   {main}
    assign(ftox,'x2.dat');
    reset(ftox);
    10:initialization;
    kuang;trb:=false;
    dosetcolor(1);set_back(1);
    15: quitt;
    qq:=getmaxx  div 2;ww:=getmaxy div 2;
    moveto(qq,ww);
    movespeed:='s';mmove('s');
    20:readkeybd(ch,b);
    if(ch='r')and(not b) then docircle;
    if(ch='f')and (not b) then doline;
    if(ch='s')and (not b) then
              begin
                 sound(2111);
                 delay(133);
                 nosound;
                 dosave;
              end;
    if (ch='c')and(not b) then dohu;
      if (ch='d')and(not b) then
                   begin
                     setfillstyle(1,getcolor);
                     floodfill(qq,ww,getcolor);
                     beep(2222);
                   end;
    if (ch='q')and(not b) then quitt;
    if (ch='w')and (not b) then begin closegraph;goto 10;end;
    if (ch='a') then begin movespeed:='f';beep(2000);end;
    if (ch='z') then begin movespeed:='s';beep(2222);end;
    if (ch='[')and(not b) then    doSetColor(1);
    if(ch=']')and not(b)      then set_back(1);
    if(ch='}')    then begin set_back(-1);sound(2111);delay(11);nosound;end;
    if (ch='{')   then  dosetcolor(-1);
    if (ch='h')and(not b )then showHelp;

    if (ch='e') and(not b) then
                  begin  trb:=not trb; beep(2033);end;
    if(ch in[#75,#77,#72,#80])and (b) then mmove(movespeed);
    if (ch='x')and(not b) then showAgain(qq,ww);
    if not(ch=#27) then
                      begin
                       goto 20;
                      end;
    if not again then begin
                   outtextxy(20,400,'Please look the screen carefully !   And press the enter key!');
                   assign (ftox,'x.dat');
                   reset(ftox);
                   again:=true;
                   readln;        qq:=32;ww:=32;
                   goto 20;
                end;
    outtextxy(22,455,'Press Enter key................');
    readln;
    closegraph;
    close(ftox);

end.