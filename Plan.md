Specificatie 1.0:
	Usecase 1.1:
		Classes = {System, Device, Jobs}
			Class System:
				-has constructor (empty for now)
				-has vector of devices
				-has vector of Jobs
				-(has Totaal emmision)* => Currently not nessecery for this usecase 	
				
				Methodes:
					-ReadData => calls functions {ReadDevice(s)[inputs: XML node][Require: input is valid] [Ensure : "name" is string, "emissions" is int, "speed" is int], 
								     ReadJob(s)[inputs: XML node] [Require: input is valid] [Ensure : "jobNumber" is int, "pageCount", is int, "userName", is string]}	
						 										
				
			Class Device:
				-has two constructors:[Device(string name, int emmison, int speed), Device(XML node)]
				-has name
				-has emmision
				-has speed
				
				
			Class Job:
				-has two constructors: [Job(int jobnumber, int pagecount, string username), Job(XML node)]
				-has jobnumber
				-has pagecount
				-has username
				
		
		
