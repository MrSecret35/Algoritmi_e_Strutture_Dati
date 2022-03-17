package grafi;

import java.util.Vector;

public class vertice_G{

	private int vertice;
	private Vector<arco_G> sorg;	//archi che portano il vertice alla sorgente
	private Vector<arco_G> inu;		//archi rimpiazzabili()

	//costruttore di un nuovo vertice
	public vertice_G(int vertice){
		sorg = new Vector<arco_G>(0);
		inu = new Vector<arco_G>(0);
		this.vertice=vertice;
	}

	//aggiunge un nuovo arco alla fine
	public void add_arco_s(int sorgente, int destinazione, int peso){
		arco_G tmp= new arco_G(sorgente, destinazione, peso);
		sorg.add(tmp);
	}

	//copia gli archi_sorg del vertice tmp
	public void cas(vertice_G tmp){
		Vector<arco_G> tmp_cp=tmp.getSorg();
		sorg.removeAllElements();
		for (int i=0; i<tmp_cp.size(); i++){
			sorg.add(tmp_cp.get(i));
		}
	}

	public Vector<arco_G> getSorg(){
		return sorg;
	}

	public String toString(){
		String s= ""+ vertice+": ";
		for (int i=0; i<sorg.size(); i++) {
			s=s + sorg.get(i).getSorgente()+"-" +sorg.get(i).getDestinazione()+ "  ";
		}
		return s;
	}

}