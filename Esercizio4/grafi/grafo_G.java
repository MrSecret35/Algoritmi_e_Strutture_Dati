package grafi;

import java.util.Vector;
import java.util.HashMap;
import java.util.Collection;

public class grafo_G{

	private Vector<arco_G> archi;
	private HashMap<Integer, vertice_G> vertici;
	private int sorgente;

	private HashMap<Integer, Vector<arco_G>> archi_sos;//archi sospesi

	public grafo_G(){
		archi= new Vector<arco_G>();
		vertici = new HashMap<Integer, vertice_G>();
		sorgente=-1;
		archi_sos= new HashMap<Integer, Vector<arco_G>>();
	}

	/*
	* restituisce YES se new_arco migliora il grafo
	* NO altrimenti
	*/
	public String migliora(arco_G new_arco){
		if(vertici.containsKey(new_arco.getSorgente()) && vertici.containsKey(new_arco.getDestinazione())){	
			Vector<arco_G> a1= vertici.get(new_arco.getDestinazione()).getSorg();
			Vector<arco_G> a2= vertici.get(new_arco.getSorgente()).getSorg();

			Vector<arco_G> a= intersezione_archi(a1,a2);

			for (int i=0; i<a.size(); i++) {
				if(a.get(i).getPeso()> new_arco.getPeso()){
					return "YES";
				}
			}
		}
		return "NO";
	}

	/*
	* effettua una insersezione tra due archi
	* restituisco un vettore con gli elementi non in comune
	*/
	private Vector<arco_G> intersezione_archi(Vector<arco_G> a, Vector<arco_G> b){
		Vector<arco_G> inter= new Vector<arco_G>();
		int i=0;
		for (i=0; i<a.size() && i<b.size() && a.get(i).isEquals(b.get(i)); i++) {}

		for (int j=i; j<a.size() ; j++){
			inter.add(a.get(j));
		}
		for (int j=i; j<b.size() ; j++){
			inter.add(b.get(j));
		}

		return inter;
	}

	/*
	private Vector<Integer> restore(Vector<Integer> x){
		Vector<Integer> tmp= new Vector<Integer>();

		for (int i=0; i<archi_sos.size(); i++){

			int j= ug_arc_int(archi_sos.get(i), x);

			if(j>0) {
				tmp.add(j);
				add_arco_restore(archi_sos.get(i).getSorgente(), archi_sos.get(i).getDestinazione(), archi_sos.get(i).getPeso());
				archi_sos.remove(i);
				i--;
			}
			//add_arco_restore();
			
		}
		//System.out.println("grandezza:    "+ archi_sos.size());
		//if(tmp.size()>0) restore(tmp); 
		return tmp;
	}
	*/

	/*
	* metodo utilizzato per inserire un arco sospeso
	*/
	private Vector<Integer> restore(Vector<Integer> x){
		Vector<Integer> tmp= new Vector<Integer>();

		for (int i=0; i<x.size(); i++){
			if(archi_sos.containsKey(x.get(i))){

				Vector<arco_G> tmp1 = archi_sos.get(x.get(i));
				for (int j=0; j<tmp1.size();j++) {

					int z= ug_arc_int(tmp1.get(j), x.get(i));
					tmp.add(z);

					add_arco_restore(tmp1.get(j).getSorgente(), tmp1.get(j).getDestinazione(), tmp1.get(j).getPeso());

				}
				archi_sos.remove(x.get(i));
			}
		}
		return tmp;
	}
	

	/*
	* confronta un arco con un vettore di interi
	* restituisce l'opposto in un arco
	* ES: se la sorgente è uguale ad un x restituisce la destinazione
	*/
	private int ug_arc_int(arco_G tmp, Vector<Integer> x){

		for (int i=0; i<x.size() ; i++) {
			if(tmp.getDestinazione()==x.get(i)){
				return tmp.getSorgente();
			}
			if(tmp.getSorgente()==x.get(i)){
				return tmp.getDestinazione();
			}
		}

		return -1;
	}
	
	/*
	* confronta un arco con un intero
	* restituisce l'opposto in un arco
	* ES: se la sorgente è uguale ad un x restituisce la destinazione
	*/
	private int ug_arc_int(arco_G tmp, int x){

		if(tmp.getDestinazione()==x){
			return tmp.getSorgente();
		}
		if(tmp.getSorgente()==x){
			return tmp.getDestinazione();
		}

		return -1;
	}

	public String toString(){
		String s= "\n";
		for(vertice_G tmp:vertici.values()){
			s=s+tmp.toString()+" \n";
		}

		return s;
	}




	/*
	* metodo utilizzato per l'aggiunta di un arco
	*/
	public void add_arco(int sorgente, int destinazione, int peso){
		archi.add(new arco_G(sorgente, destinazione, peso));
		
		if(vertici.size()==0 || sorgente<0){//primo elemento che diventa sorgente
			this.sorgente=sorgente;
			vertice_G s= new vertice_G(sorgente);
			vertici.put(sorgente, s);
			add_arco(sorgente, destinazione, peso);
			return;
		}

		if(vertici.containsKey(sorgente) && vertici.containsKey(destinazione)){

			//arco già esistente
			//System.out.println("ciaooooo");

		}else if(vertici.containsKey(sorgente) && !vertici.containsKey(destinazione)){
			//add_arco(destinazione, sorgente, peso);

			vertice_G tmp= new vertice_G(destinazione);
			//copio tutti gli archi per arrivare alla sorgente dell'arco
			vertice_G ar= vertici.get(sorgente);
			tmp.cas(ar);
			tmp.add_arco_s(sorgente, destinazione, peso);

			vertici.put(destinazione, tmp);
			
			//System.out.println(vertici.containsKey(destinazione));



			Vector<Integer> x=new Vector<Integer>();
			x.add(destinazione);

			Vector<Integer> t= restore(x);//aggiungo tutti i rami che richiedevano il nuovo vertice
			x.clear();
			while(!t.isEmpty()){
				System.gc();
				t=restore(t);
			}


		}else if(!vertici.containsKey(sorgente) && vertici.containsKey(destinazione)){
			//add_arco(destinazione, sorgente, peso);

			vertice_G tmp= new vertice_G(sorgente);
			//copio tutti gli archi per arrivare alla sorgente dell'arco
			vertice_G ar= vertici.get(destinazione);
			tmp.cas(ar);
			tmp.add_arco_s(destinazione, sorgente, peso);

			vertici.put(sorgente, tmp);



			Vector<Integer> x=new Vector<Integer>();
			x.add(sorgente);
			Vector<Integer> t= restore(x);//aggiungo tutti i rami che richiedevano il nuovo vertice
			x.clear();
			while(!t.isEmpty()){
				System.gc();
				t=restore(t);
			} 

		}else{

			//archi_sos.add(p);

			arco_G p= new arco_G(sorgente, destinazione, peso);
			if(archi_sos.containsKey(sorgente)){
				Vector<arco_G> tmp= archi_sos.get(sorgente);
				tmp.add(p);
				archi_sos.put(sorgente,tmp);
			}else{
				Vector<arco_G> tmp= new Vector<arco_G>(0);
				tmp.add(p);
				archi_sos.put(sorgente,tmp);
			}

			p = new arco_G(destinazione, sorgente, peso);

			if(archi_sos.containsKey(destinazione)){
				Vector<arco_G> tmp= archi_sos.get(destinazione);
				tmp.add(p);
				archi_sos.put(destinazione,tmp);
			}else{
				Vector<arco_G> tmp= new Vector<arco_G>(0);
				tmp.add(p);
				archi_sos.put(destinazione,tmp);
			}
		}
	}

	/*
	* metodo utilizzato per l'aggiunta di un arco sospeso
	*/
	private void add_arco_restore(int sorgente, int destinazione, int peso){

		if(vertici.containsKey(sorgente) && vertici.containsKey(destinazione)){

			//arco già esistente
			//

		}else if(vertici.containsKey(sorgente) && !vertici.containsKey(destinazione)){
			//add_arco(destinazione, sorgente, peso);

			vertice_G tmp= new vertice_G(destinazione);
			//copio tutti gli archi per arrivare alla sorgente dell'arco
			vertice_G ar= vertici.get(sorgente);
			tmp.cas(ar);
			tmp.add_arco_s(sorgente, destinazione, peso);

			vertici.put(destinazione, tmp);

		}else{
			add_arco_restore(destinazione, sorgente, peso);
		}
	}
}