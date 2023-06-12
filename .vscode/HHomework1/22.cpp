void ChessPath(ChessBoard &C,position p){//输入棋盘以及初始位置
        int a[30] = {0};
        SStack S; StackInit(S);
        //将初始位置压入栈中
        Push(S,p);
        int count = 0;
        while(!Stackempty){
            count += 1;
            position e;
            Pop(S,e);//避免以后回溯的时候还tm回溯到原来的元素
            visited[e.x][e.y] = true;
            C.a[e.x][e.y] = count;
            int cangoways = howmany_ways_cango(S,e);
            



        }



        void ChessPath(ChessBoard &C,position p){//输入棋盘以及初始位置
        int a[30] = {0};
        SStack S; StackInit(S);
        //将初始位置压入栈中
        Push(S,p);
        int count = 0;
        while(count != N*N){//当
            count += 1;
            position newp;
            Pop(S,newp);//取出当前位置(走过去),同时防止之后进死循环
            visited[newp.x][newp.y] = true;//将当前位置标记为已访问
            C.a[newp.x][newp.y] = count; //标记路径数组中的顺序
            int cangoways = howmany_ways_cango(S,newp);//返回并把符合条件的下一个位置入栈
                a[count] = cangoways;
               if (cangoways == 0) {
                //如果回退到的位置已经访问过了，说明这是条死路，要到上一个cangoways>=2的地方去
                    while(1){
                    position pre_pos;
                    Gettop(S,pre_pos);
                    if(only_return_thenumber(S,pre_pos) <= 2){
                        Pop(S, pre_pos);
                        visited[pre_pos.x][pre_pos.y] = false; // 回溯过程中需要将已访问标记置为 false
                        C.a[pre_pos.x][pre_pos.y] = 0; // 将该位置标记为未走过
                        a[count-1]--;
                        if (a[count-1] == 0) count--;
                    }
                    else {
                        if(a[count]==0) {
                            position e;
                            Pop(S,e);
                        }
                        count --;
                        break;}
                    }
                    
                    
                
        }             
    }
        cout << endl;
        prinln_the_result(C.a);
}