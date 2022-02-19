class PatientInfoTable:
    def __init__(self, patient_id,  doctor_id, name, surname, email, password, age, gender=None, city=None,
            body_height= None, body_mass_index= None, body_weight= None, blood_pressure_risk= None, cholesterol_risk=None, confirmed = False,id=None,
            hemoglobin_a1c= None, high_density_lipoprotein_cholesterol= None, low_density_lipoprotein_cholesterol= None, total_cholesterol= None, 
            triglycerides= None, calcium= None, carbon_dioxide= None,
            chloride= None, creatinine= None, glucose= None, potassium= None, sodium= None, urea_nitrogen= None,
            glomerular_filtration= None, microalbumin= None, fev1_fvc= None

            ):
        
        """
             oral_temp= None, 
             hemoglobin_gastro= None, ployp_size= None, 
            american_house_dust= None, cat_danger= None, cladosporium= None, codfish= None, common_ragweed= None, 
            cow_milk= None, egg_white= None,
            honey_bee= None, latex= None, peanut= None, shrimp= None, soybean= None, walnut= None, white_oak= None,  
            total_mmse= None, dxa_bone_density= None, , 
            eczema_head_neck= None, eczema_lower= None, eczema_trunk= None, eczema_upper= None, history_visit= None, 
            diastolic_blood_pressure = None, 
            systolic_blood_pressure = None
            """

        self.patient_id                           = patient_id
        self.doctor_id                            = doctor_id
        #self.patient_info_id                      = patient_info_id
        self.name                                 = name
        self.surname                              = surname
        self.email                                = email
        self.password                             = password
        self.age                                  = age                                  
        self.gender                               = gender                                 
        self.city                                 = city          
        self.body_height                          = body_height
        self.body_mass_index                      = body_mass_index
        self.body_weight                          = body_weight
        self.blood_pressure_risk                  = blood_pressure_risk
        self.cholesterol_risk                     = cholesterol_risk
        self.confirmed                            = confirmed
        self.id                                   = id

        self.hemoglobin_a1c                       = hemoglobin_a1c                      
        self.high_density_lipoprotein_cholesterol = high_density_lipoprotein_cholesterol
        self.low_density_lipoprotein_cholesterol  = low_density_lipoprotein_cholesterol 
        self.total_cholesterol                    = total_cholesterol                     
        self.triglycerides                        = triglycerides                        
        self.calcium                              = calcium                               
        self.carbon_dioxide                       = carbon_dioxide                         
        self.chloride                             = chloride                              
        self.creatinine                           = creatinine                              
        self.glucose                              = glucose                                  
        self.potassium                            = potassium                              
        self.sodium                               = sodium                                    
        self.urea_nitrogen                        = urea_nitrogen                             
        self.glomerular_filtration                = glomerular_filtration                    
        self.microalbumin                         = microalbumin                              
        self.fev1_fvc                             = fev1_fvc                                       
