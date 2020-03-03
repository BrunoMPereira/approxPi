import java.util.Random;
public class approxPi{
	
	static int R = 1;
	static int inside;
	public static void main(String args[]){
		long start = System.currentTimeMillis();
		Random r = new Random();
		
		int nPoints = Integer.parseInt(args[0]);
			
		for(int i = 0; i<nPoints;i++){
			step();
		}
		
		System.out.println("Total Number of points: " + nPoints);
		System.out.println("Points within circle: " + inside);
		System.out.println("Pi estimation: " + 4*(inside/nPoints));
		
		System.out.println("Elapsed " + (System.currentTimeMillis() - start));
			
		
	}
	
	public static step(){
		if(isInsideCircle(r.nextDouble(), r.nextDouble()))
				inside++;
	}
	
	
	private static boolean isInsideCircle(double x, double y){
		return x*x + y*y <= R;	
	}
}




