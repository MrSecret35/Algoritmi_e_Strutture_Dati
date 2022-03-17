import grafi.arco_G;
import grafi.grafo_G;

import java.util.Vector;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.Scanner;

import java.io.FileWriter;
import java.io.BufferedWriter;

public class oc{
	
	private static void printUsage(){
		System.out.println("Invalid argument");
		System.out.println("first name= input \n second name= correct");
	}


	public static void main(String[] args){
		/*
		if(args.length!=2){
			printUsage();
			System.exit(0);
		}
		*/
		try{
			//long start = System.currentTimeMillis();

			String[] result= run_test("args[0]");
			//write_data("args[1]",result);
			//boolean res= cmp_array(result,result_dc);

			//long end = System.currentTimeMillis();
			//long elapsedTime = end - start;
			//double time  =elapsedTime/1000.00;
			//System.out.println("Time used " + time+ " sec");
			
		}catch(Exception e){
			printUsage();
			System.exit(0);
		}
		
	}

	public static String[] run_test(String inp){
		String[] res= new String[0];
		try{
			//BufferedReader br= new BufferedReader(new FileReader("input.txt"));
			Scanner br= new Scanner(System.in);

			grafo_G grafo= new grafo_G();
			
			String tmp = br.nextLine();

			int n_arc= Integer.parseInt(tmp)-1;
			for (int i=0; i<n_arc; i++) {
				tmp = br.nextLine();
				String[] tmpmini=tmp.split(" ");
				int s=Integer.parseInt(tmpmini[0]);
				int d=Integer.parseInt(tmpmini[1]);
				int c=Integer.parseInt(tmpmini[2]);
				grafo.add_arco(s,d,c);
			}
			tmp = br.nextLine();
			int n_op=Integer.parseInt(tmp);
			//System.out.println("devo fare : "+ n_op+ " operazioni");

			res= new String[n_op];
			for (int i=0; i<n_op; i++) {
				tmp = br.nextLine();

				String[] tmpmini=tmp.split(" ");
				int s=Integer.parseInt(tmpmini[0]);
				int d=Integer.parseInt(tmpmini[1]);
				int c=Integer.parseInt(tmpmini[2]);
				arco_G new_arco=new arco_G(s,d,c);

				res[i]=grafo.migliora(new_arco);
				System.out.println(res[i]);
			}
			br.close();
		}catch(Exception e){
			System.out.println("Errore durante le operazioni di calcolo");
			System.exit(0);
		}
		

		return res;
	}

	public static void write_data(String filename, String[] result){
		
		try{
			BufferedWriter b=new BufferedWriter (new FileWriter("output.txt"));
			for (int i=0; i<result.length; i++) {

				String tmp = result[i]+"\n";

				b.write(tmp);
			}
			b.close();
		}catch(Exception e){
			//printUsage();
			System.out.println("Errore durante il caricamento dei risultati");
			System.exit(0);
		}
	}

}