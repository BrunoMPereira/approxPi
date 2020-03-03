import java.util.Random;
public class approxPiMT{
	static int R = 1;
	static double insides[];
	public static void main(String args[]){
		Random r = new Random();
		
		int nPoints = Integer.parseInt(args[0]);
		int nThreads = Integer.parseInt(args[1]);
		
		Thread threads[] = new Thread[nThreads]; 		
		double totalInside = 0;
		
		insides = new double[nThreads];
		

		for(int i = 0; i<nThreads;i++){
			Thread t = step(r, nPoints, nThreads, i);
			t.start();			
			threads[i] = t;
		}
		
		try{
		for (Thread t : threads){
    			t.join();
		}
		}catch(InterruptedException e){
			e.printStackTrace();
		}	
		
		for(int i = 0; i < nThreads;i++){
			totalInside+= insides[i];
		}
			
		System.out.println("Total Number of points: " + nPoints);
		System.out.println("Points within circle: " + totalInside);
		System.out.println("Pi estimation: " + 4*(totalInside/nPoints));	
	}
	
	public static Thread step(Random r, int nPoints, int nThreads, int threadID){
		return new Thread(() -> {
			double countInside = 0;
			for(int i=0; i<nPoints/nThreads;i++){
				System.out.println(i  + " on " + threadID);
				if(isInsideCircle(r.nextDouble(), r.nextDouble()))
					countInside++;
			}
			insides[threadID] = countInside;
		});
	}
	
	
	private static boolean isInsideCircle(double x, double y){
		return x*x + y*y <= R;	
	}
}




