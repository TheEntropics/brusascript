import java.lang.*;
import java.math.*;
import java.util.*;
import java.io.*;

public class JAVA
{
    public static void main(String[] args) throws FileNotFoundException
    {
        Scanner in;
        Random r = new Random();
        if(args.length > 0)
        {
            in = new Scanner(new File(args[0]));
        }
        else
        {
            in = new Scanner(System.in);
        }
        while(in.hasNextLine())
        {
            String line = in.nextLine().toUpperCase();
            String[] words = line.split(" ");
            for(int i = 0; i < words.length; i++)
            {
                int swap_count = 0;
                StringBuilder tmp = new StringBuilder(words[i]);
                for(int j = 0; j < words[i].length() - 1; j++)
                {
                    if(swap_count < 2 && r.nextInt(100) < 20)
                    {
                        swap_count++;
                        char c = tmp.charAt(j);
                        tmp.setCharAt(j, tmp.charAt(j + 1));
                        tmp.setCharAt(j + 1, c);
                    }
                }
                words[i] = tmp.toString();
            }
            for(int i = 0; i < words.length; i++)
            {
                int max_del = words[i].length() / 5;
                int act_del = 0;
                StringBuilder tmp = new StringBuilder(words[i]);
                for(int j = 0; j < tmp.length(); j++)
                {
                    int prob;
                    if(j < tmp.length() - 1 && tmp.charAt(j) == tmp.charAt(j + 1))
                    {
                        prob = 40;
                    }
                    else if(tmp.charAt(j) == 'A' || tmp.charAt(j) == 'E' || tmp.charAt(j) == 'I' || tmp.charAt(j) == 'O' || tmp.charAt(j) == 'U')
                    {
                        prob = 5;
                    }
                    else
                    {
                        prob = 10;
                    }
                    if(act_del < max_del && r.nextInt(100) < prob)
                    {
                        act_del++;
                        tmp.deleteCharAt(j);
                        j--;
                    }
                }
                words[i] = tmp.toString();
            }
            for(int i = 0; i < words.length; i++)
            {
                System.out.print(words[i] + " ");
            }
            if(r.nextInt(100) < 30)
            {
                System.out.print("H!?");
            }
            System.out.println();
        }
    }
}
