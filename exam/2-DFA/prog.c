    #include <stdio.h>
    void main()
    {
        int state[10];
        int str[10], input[10];
        char ch;
        int x[20];
        int s, n, k = 0, j, a, i, l, t, q = 0, fs, b, nxt, z;
        printf("Enter the no of states\n");
        scanf("%d", &s);
        printf("enter the no of inputs\n");
        scanf("%d", &n);
        for (i = 0; i < s; i++)
        {
            printf("Enter the state\n");
            scanf("%d", &state[i]);
            printf("is it final state?... .y..1/n..0\n");
            scanf("%d", &a);
            if (a == 1)
                fs = state[i];
        }
        printf("Enter the inputs\n");
        for (i = 0; i < n; i++)
            scanf("%d", &input[i]);
        printf("Transition state\n");
        for (i = 0; i < s; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("(q%d,%d)=q", state[i], input[j]);
                scanf("%d", &b);
                x[k] = b;
                k++;
            }
        }
        do
        {
            printf("Enter the length of the string\n");
            scanf("%d", &l);
            printf("Enter the input string\n");
            q = 0;
            for (i = 0; i < l; i++)
            {
                scanf("%d", &str[i]);
            }
            for (i = 0; i < l; i++)
            {
                t = 0;
                do
                {
                    if (str[i] == input[t])
                    {
                        nxt = x[n * q + t];
                        for (j = 0; j < s; j++)
                        {
                            if (nxt == state[j])
                                q = j;
                        }
                        t++;
                    }
                    else
                        t++;
                } while (t != n);
            }
            if (nxt == fs)
                printf("\n string is accepted\n");
            else
                printf("\nstring is not accepted\n");
            printf("do you want to continue..if yes press 1 else 0\n");
            scanf("%d", &z);
        } while (z != 0);
    }
