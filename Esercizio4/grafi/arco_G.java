package grafi;

public class arco_G{
		private int sorgente;
		private int destinazione;
		private int peso;

		public arco_G(int sorgente, int destinazione, int peso){
			this.sorgente=sorgente;
			this.destinazione=destinazione;
			this.peso=peso;
		}

		public int getDestinazione(){
			return destinazione;
		}

		public int getSorgente(){
			return sorgente;
		}

		public int getPeso(){
			return peso;
		}

		/*
		* restituisce true 	se i due archi sono uguali 
		* false 			altrimenti
		*/
		public boolean isEquals(arco_G b){
			if(sorgente==b.getSorgente() && destinazione==b.getDestinazione()){
				return true;
			}
			return false;
		}

}