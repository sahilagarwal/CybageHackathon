import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class KMP_String_Matching
{
    public
    int c=0;
    
    void KMPSearch(String pat, String txt)
    {
        int M = pat.length();
        int N = txt.length();
        
        // create lps[] that will hold the longest prefix suffix
        // values for pattern
        int lps[] = new int[M];
        int j = 0;  // index for pat[]
        
        // Preprocess the pattern (calculate lps[] array)
        computeLPSArray(pat,M,lps);
        
        int i = 0;  // index for txt[]
        while(i < N)
        {
            if(pat.charAt(j) == txt.charAt(i))
            {
                j++;
                i++;
            }
            if(j == M)
            {
                c++;
                //System.out.println("Found pattern at index " + (i-j));
                j = lps[j-1];
            }
            
            // mismatch after j matches
            else if(i < N && pat.charAt(j) != txt.charAt(i))
            {
                // Do not match lps[0..lps[j-1]] characters,
                // they will match anyway
                if(j != 0)
                    j = lps[j-1];
                else
                    i = i+1;

            }
        }
    }
    
    void computeLPSArray(String pat, int M, int lps[])
    {
        int len = 0;  // length of the previous longest prefix suffix
        int i = 1;
        lps[0] = 0;  // lps[0] is always 0
        
        // the loop calculates lps[i] for i = 1 to M-1
        while(i<M)
        {
            if(pat.charAt(i) == pat.charAt(len))
            {
                len++;
                lps[len] = len;
                i++;
            }
            else  // (pat[i] != pat[len])
            {
                if(len != 0)
                {
                    // This is tricky. Consider the example
                    // AAACAAAA and i = 7.
                    len = lps[len-1];
                    
                    // Also, note that we do not increment i here
                }
                else  // if (len == 0)
                {
                    lps[i] = len;
                    i++;
                }
            }
        }
        
    }
    public static void readFileAndPrintCounts(String crunchifyFile) throws FileNotFoundException {
    	 
        int myWordscount = 0;
        int mySentcount = 0;
        int crunchifyTotalCharacters = 0;
        String[] mySent = null;

        String mydata;
 
        try (BufferedReader crunchifyBuffer = new BufferedReader(new FileReader(crunchifyFile)))
        {
            // read each line one by one
            while ((mydata = crunchifyBuffer.readLine()) != null)
            {
                
 
                // ignore multiple white spaces
                //String[] myWords = mydata.split(" ");
                 //mySent = mydata.;
                
                for(int i=0;i<mydata.length();i++)
                {
                    if(mydata.charAt(i) == ' ')
                    {
                        myWordscount++;
                        
                    }
                    else if(mydata.charAt(i) == '.')
                    {
                        mySentcount++;
                    }
                    
                }
                myWordscount +=1;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
 
        System.out.println(("* Total Words: " + (myWordscount)));
        System.out.println(("* Toal sentens: " + mySentcount));
    }
    // Driver program to test above function
    public static void main(String args[]) throws IOException
    {
    	
    	//BufferedReader br=new BufferedReader(new FileReader("//home/sahilnew/input.txt"));
        //out = new FileOutputStream("//home/sahilnew/output.txt");
        //System.out.print("in try");
        KMP_String_Matching obj1 = new KMP_String_Matching();
        //int c;
        readFileAndPrintCounts("//home/sahilnew/input.txt");
        String txt="hello.";
        BufferedReader br=new BufferedReader(new FileReader("//home/sahilnew/input.txt"));
        int sum=0;
        for (String line;(line=br.readLine())!=null;)
        {
       	 //System.out.println(line);
       	obj1.KMPSearch(txt,line);
        //sum+=obj1.c;
        }
        System.out.println(obj1.c);
    }
}