void _init()
{
    if (__gmon_start__ != 0)
        __gmon_start__();
}

int64_t sub_1020()
{
    int64_t var_8 = data_3ff0;
    /* jump -> data_3ff8 */
}

char* strncpy(char* arg1, char const* arg2, uint64_t arg3)
{
    /* tailcall */
    return strncpy(arg1, arg2, arg3);
}

int64_t sub_1036()
{
    int64_t var_8 = 0;
    /* tailcall */
    return sub_1020();
}

int32_t puts(char const* str)
{
    /* tailcall */
    return puts(str);
}

int64_t sub_1046()
{
    int64_t var_8 = 1;
    /* tailcall */
    return sub_1020();
}

int32_t fclose(FILE* fp)
{
    /* tailcall */
    return fclose(fp);
}

int64_t sub_1056()
{
    int64_t var_8 = 2;
    /* tailcall */
    return sub_1020();
}

uint64_t strlen(char const* arg1)
{
    /* tailcall */
    return strlen(arg1);
}

int64_t sub_1066()
{
    int64_t var_8 = 3;
    /* tailcall */
    return sub_1020();
}

void __stack_chk_fail() __noreturn
{
    /* tailcall */
    return __stack_chk_fail();
}

int64_t sub_1076()
{
    int64_t var_8 = 4;
    /* tailcall */
    return sub_1020();
}

void setbuf(FILE* fp, char* buf)
{
    /* tailcall */
    return setbuf(fp, buf);
}

int64_t sub_1086()
{
    int64_t var_8 = 5;
    /* tailcall */
    return sub_1020();
}

int32_t printf(char const* format, ...)
{
    /* tailcall */
    return printf();
}

int64_t sub_1096()
{
    int64_t var_8 = 6;
    /* tailcall */
    return sub_1020();
}

char* fgets(char* buf, int32_t n, FILE* fp)
{
    /* tailcall */
    return fgets(buf, n, fp);
}

int64_t sub_10a6()
{
    int64_t var_8 = 7;
    /* tailcall */
    return sub_1020();
}

FILE* fopen(char const* filename, char const* mode)
{
    /* tailcall */
    return fopen(filename, mode);
}

int64_t sub_10b6()
{
    int64_t var_8 = 8;
    /* tailcall */
    return sub_1020();
}

int32_t __isoc99_scanf(char const* format, ...)
{
    /* tailcall */
    return __isoc99_scanf();
}

int64_t sub_10c6()
{
    int64_t var_8 = 9;
    /* tailcall */
    return sub_1020();
}

void exit(int32_t status) __noreturn
{
    /* tailcall */
    return exit(status);
}

int64_t sub_10d6()
{
    int64_t var_8 = 0xa;
    /* tailcall */
    return sub_1020();
}

void _start(int64_t arg1, int64_t arg2, void (* arg3)()) __noreturn
{
    int64_t stack_end_1;
    int64_t stack_end = stack_end_1;
    __libc_start_main(main, __return_addr, &ubp_av, nullptr, nullptr, arg3, &stack_end);
    /* no return */
}

void deregister_tm_clones()
{
    return;
}

void sub_1140()
{
    return;
}

void _FINI_0()
{
    if (data_4088 != 0)
        return;
    
    if (__cxa_finalize != 0)
        __cxa_finalize(__dso_handle);
    
    deregister_tm_clones();
    data_4088 = 1;
}

void _INIT_0()
{
    /* tailcall */
    return sub_1140();
}

void* get_flag(char* flag, long unsigned int max_length)
{
    FILE* fp = fopen("flag", &data_201e);
    
    if (fp == 0)
    {
        strncpy(flag, placeholder_flag, (max_length - 1));
        void* result = &flag[(max_length - 1)];
        *result = 0;
        return result;
    }
    
    if (fgets(flag, max_length, fp) != 0)
    {
        uint64_t rax_4 = strlen(flag);
        
        if ((rax_4 != 0 && flag[(rax_4 - 1)] == 0xa))
            flag[(rax_4 - 1)] = 0;
    }
    
    return fclose(fp);
}

int throw_hands(int choice)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    puts("Your move: (0: Rock, 1: Paper, 2…");
    int u;
    __isoc99_scanf(&data_2054, &u);
    
    if ((u < 0 || u > 2))
    {
        puts("Invalid move! No cheating >:(.");
        exit(0);
        /* no return */
    }
    
    if (((u == 0 && choice == 1) || ((u == 1 && choice == 2) || ((u == 2 && choice == 0) || choice == u))))
    {
        puts("Womp womp, I win!");
        exit(0);
        /* no return */
    }
    
    puts("You won this round!");
    *(fsbase + 0x28);
    
    if (rax == *(fsbase + 0x28))
        return 1;
    
    __stack_chk_fail();
    /* no return */
}

void make_moves(char* in, int* out)
{
    int32_t delta = 0;
    
    for (int i = 0; i <= 9; i += 1)
    {
        in[i] += delta;
        char rax_12 = in[i];
        char rdx_6 = ((rax_12 >> 7) >> 6);
        out[i] = (((rax_12 + rdx_6) & 3) - rdx_6);
        delta = ((in[i] + 0x1ca3) % 0x15);
    }
}

int32_t main()
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    setbuf(stdin, nullptr);
    setbuf(__TMC_END__, nullptr);
    char flag[0x64];
    get_flag(&flag, 0x64);
    puts("Welcome to Rock-Paper-Scissors! …");
    printf("Enter your name: ");
    char name[0x64];
    int32_t result;
    
    if (fgets(&name, 0x64, stdin) == 0)
    {
        puts("Error reading name!");
        result = 1;
    }
    else
    {
        uint64_t rax_3 = strlen(&name);
        
        if ((rax_3 != 0 && name[(rax_3 - 1)] == 0xa))
            name[(rax_3 - 1)] = 0;
        
        if (rax_3 <= 0xa)
        {
            puts("That can't be right, enter a lon…");
            exit(0);
            /* no return */
        }
        
        printf("Hello, %s! Let's start the game.…", &name);
        int moves[0xa];
        make_moves(&name, &moves);
        
        for (int i = 0; i <= 9; i += 1)
            throw_hands(moves[i]);
        
        printf("Wow, good job! Here's your flag:…", &flag);
        result = 0;
    }
    
    *(fsbase + 0x28);
    
    if (rax == *(fsbase + 0x28))
        return result;
    
    __stack_chk_fail();
    /* no return */
}

int64_t _fini() __pure
{
    return;
}

