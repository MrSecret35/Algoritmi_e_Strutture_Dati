
import java.util.Vector;
import java.io.FileReader;
import java.io.BufferedReader;

import Distance.Edit_Distance;



public class CorrectionTextApp{

	private static int MAX_DIST=64;
	private static String filename;
	private static Vector<String> dictionary;

	public static void main(String args[]){
		Vector<String> array = loadData(args);
		array= vectorClean(array);
		correzione(array);
	}

	private static void printUsage(){
		System.out.println("Invalid argument");
		System.out.println("first name= DICTIONARY \n second name= FILENAME");
	}

	/*
	* carica l'intero file in un vector che restituisce
	* carica il dizionario nel vector dictionary
	*/
	private static Vector<String> loadData(String[] args){
		if(args.length!=2){
			printUsage();
			System.exit(0);
		}
		filename=args[1];

		try{
			BufferedReader br= new BufferedReader(new FileReader(filename));
		
			Vector<String> array=new Vector<String>(5);
			
			while( br.ready()){
				String tmp = br.readLine();
				String[] tmpmini=tmp.split(" ");

				for (int i=0; i<tmpmini.length;i++ ) {
					array.addElement(tmpmini[i]);
				}
			}
			br.close();
			BufferedReader br1= new BufferedReader(new FileReader(args[0]));
			dictionary=new Vector<String>(5);
			
			while( br1.ready()){
				String tmp = br1.readLine();
				String[] tmpmini=tmp.split(" ");

				for (int i=0; i<tmpmini.length;i++ ) {
					dictionary.addElement(tmpmini[i]);
				}
			}
			br1.close();
			return array;

		}catch(Exception e){
			printUsage();
			System.exit(0);
		}
		return null;
	}

	private static Vector<String> vectorClean(Vector a){
		Vector<String> b=new Vector<String>(1);
		for (int i=0; i<a.size(); i++) {
			String s=(String)a.get(i);
			s = s.replaceAll("[^A-Za-z0-9]", "");
			s=s.trim();
			if(s.length()>0){
				b.addElement(s);
			}
		}
		b.trimToSize();
		return b;
	}

	private static void correzione(Vector<String> array){
		for (int i=0; i<array.size(); i++) {
			String s=array.get(i);

			System.out.println(s + ":");

			int[] distanza = distMin(s);
			if(distanza[0] != 0){ 
				stampaParole(distanza);
			}else{
				System.out.println("\t" + s);
			}
			
		}
	}

	private static int[] distMin(String s){
		int[] dist= new int[dictionary.size()+1];
		dist[0]=MAX_DIST;//distanza minima
		for (int i=0; i<dictionary.size(); i++) {
			String tmp=dictionary.get(i);
			if((tmp.length() <= s.length() +dist[0]) && (tmp.length() >= s.length()-dist[0])){
				dist[i+1] = Edit_Distance.edit_distance_dyn(s,tmp);
			}else{
				dist[i+1] =MAX_DIST;
			}
			if(dist[i+1] < dist[0]){
				dist[0]=dist[i+1];
			}
		}
		return dist;
	}

	private static void stampaParole(int[] d){
		for (int i=0; i<dictionary.size(); i++) {
			if(d[i+1] == d[0]){
				String tmp=dictionary.get(i);
				System.out.println("\t" + tmp);
			}
		}
	}
	
}