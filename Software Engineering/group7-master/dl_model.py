
import tensorflow as tf
import pandas as pd
import numpy as np
from sklearn.impute import KNNImputer


class DLModel:
    def __init__(self):
        self.blood_model = tf.keras.models.load_model('bloodModel.h5')
        self.blood_df = pd.read_csv("bloodData.csv")
        self.blood_label = pd.read_csv("bloodLabel.csv")

        self.chol_model = tf.keras.models.load_model('cholModel.h5')
        self.chol_df = pd.read_csv("cholData.csv")
        self.chol_label = pd.read_csv("cholLabel.csv")

        self.city_labels = ['Boston' 'Hopkinton' 'Halifax' 'Attleboro' 'Springfield' 'Somerville'
                            'Andover' 'Hull' 'Bourne' 'Cambridge' 'Worcester' 'Dalton' 'Pembroke'
                            'Winchester' 'Westminster' 'Monson' 'Mattapoisett' 'Revere' 'Tewksbury'
                            'Plymouth' 'Newton' 'Concord' 'Rehoboth' 'Westwood' 'Westfield' 'Easton'
                            'Saugus' 'Great Barrington' 'Sandwich' 'Franklin Town' 'Taunton'
                            'South Hadley' 'Wilmington' 'Brewster' 'Swampscott' 'Marlborough'
                            'Barnstable Town' 'Granville' 'Framingham' 'Wareham' 'Mashpee' 'Lowell'
                            'Boxford' 'Watertown Town' 'Greenfield Town' 'Quincy' 'Rutland'
                            'Holliston' 'Shutesbury' 'Granby' 'Bellingham' 'Brookfield' 'Lynn'
                            'Milford' 'Dracut' 'Charlton' 'Freetown' 'Burlington' 'Norfolk'
                            'Mansfield' 'Norwood' 'Haverhill' 'Everett' 'Melrose' 'Stow' 'Fall River'
                            'Pepperell' 'Northfield' 'Ipswich' 'Fairhaven' 'Brookline' 'Walpole'
                            'Marshfield' 'Canton' 'Wilbraham' 'North Andover' 'Millbury' 'Gardner'
                            'Weston' 'Norwell' 'Lawrence' 'Orleans' 'New Bedford' 'Billerica'
                            'Hanover' 'Westport' 'Leominster' 'Williamstown' 'Dartmouth' 'Wayland'
                            'Medford' 'Brockton' 'Ashby' 'Waltham' 'Medway' 'Lancaster' 'Westford'
                            'Fitchburg' 'Holden' 'Winthrop Town' 'Braintree Town' 'Malden'
                            'West Springfield Town' 'Chelsea' 'Boylston' 'Auburn' 'Webster'
                            'Marblehead' 'Scituate' 'Dudley' 'Wakefield' 'Bedford' 'Reading'
                            'North Attleborough' 'Belmont' 'Sutton' 'Ayer' 'Natick' 'Falmouth'
                            'Salem' 'Kingston' 'Orange' 'Chelmsford' 'Lexington' 'Townsend' 'Norton'
                            'Holyoke' 'Weymouth Town' 'Hinsdale' 'Lynnfield' 'Milton' 'Harvard'
                            'Woburn' 'Pittsfield' 'Leicester' 'Brimfield' 'Peabody' 'Beverly'
                            'Ludlow' 'Paxton' 'Templeton' 'Wrentham' 'Yarmouth' 'Swansea'
                            'North Reading' 'Somerset' 'Bridgewater' 'Oak Bluffs' 'Arlington' 'Upton'
                            'Northbridge' 'Stoughton' 'Dedham' 'Conway' 'Longmeadow' 'Methuen Town'
                            'Randolph' 'Ashburnham' 'Danvers' 'Seekonk' 'Groveland' 'Shrewsbury'
                            'Northampton' 'Mendon' 'Palmer Town' 'Montague' 'Hardwick' 'Abington'
                            'Rockland' 'Salisbury' 'West Brookfield' 'Wellesley' 'Avon'
                            'Middleborough' 'Hamilton' 'Winchendon' 'Maynard' 'Harwich' 'Belchertown'
                            'East Bridgewater' 'Chicopee' 'Northborough' 'Millis' 'Williamsburg'
                            'Clinton' 'Amherst' 'Topsfield' 'Medfield' 'Needham' 'West Tisbury'
                            'Hingham' 'Easthampton Town' 'Wenham' 'Essex' 'Dennis' 'Ashland']

    def predict_blood(self,patient):
        """
        1-2  çok düşük
        2 düşük tansiyon
        3 normal
        4 yüksel
        5 çok yüksek
        """


        print("PREDICT FUNC")
        new_patient = np.empty(22)
        new_patient[:] = np.nan
        
        if patient.city != None and patient.city in self.city_labels:
            city_index = self.city_labels.index(patient.city)
        else:
            city_index = -1

        
        new_patient[0] = int(patient.gender == "male")       
        new_patient[1] = patient.age   
        new_patient[2] = city_index
        new_patient[3] = patient.body_height       
        new_patient[4] = patient.body_mass_index   
        new_patient[5] = patient.body_weight 
        new_patient[6] = patient.hemoglobin_a1c                      
        new_patient[7] = patient.high_density_lipoprotein_cholesterol
        new_patient[8] = patient.low_density_lipoprotein_cholesterol 
        new_patient[9] = patient.total_cholesterol                   
        new_patient[10] = patient.triglycerides                       
        new_patient[11] = patient.calcium                             
        new_patient[12] = patient.carbon_dioxide                      
        new_patient[13] = patient.chloride                            
        new_patient[14] = patient.creatinine                          
        new_patient[15] = patient.glucose                             
        new_patient[16] = patient.potassium                           
        new_patient[17] = patient.sodium                              
        new_patient[18] = patient.urea_nitrogen                       
        new_patient[19] = patient.glomerular_filtration               
        new_patient[20] = patient.microalbumin                        
        new_patient[21] = patient.fev1_fvc                            
        

        df2 = pd.DataFrame({self.blood_df.columns[i]: new_patient[i]} for i in range(22)).iloc[0]
        temp_df = pd.concat([self.blood_df, df2], ignore_index = True, axis = 0).iloc[0:-21][self.blood_df.columns[0:]]
        imputer = KNNImputer(n_neighbors=5, weights="distance")
        arr = imputer.fit_transform(temp_df)
        temp_df = pd.DataFrame(arr, columns = self.blood_df.columns)
        new_patient = temp_df.iloc[-1]
        new_patient = np.array([new_patient])

        print(self.blood_df.columns)

        estimation = self.blood_model.predict(new_patient)

        if estimation[0][2] < 2:
            patient.blood_pressure_risk = "Patient has low blood pressure."

        elif estimation[0][2] < 2.5:
            patient.blood_pressure_risk = "Patient has tendency to low blood pressure."

        elif estimation[0][2] < 3.5:
            patient.blood_pressure_risk = "Patient has normal blood pressure."

        elif estimation[0][2] < 4:
            patient.blood_pressure_risk = "Patient has tendency to high blood pressure."

        else:
            patient.blood_pressure_risk = "Patient has high blood pressure."


        return patient

    def predict_chol(self,patient):
        """
        3-4 riskli
        4-6 çok riskli
        """

        print("PREDICT FUNC")
        new_patient = np.empty(22)
        new_patient[:] = np.nan
        
        if patient.city != None and patient.city in self.city_labels:
            city_index = self.city_labels.index(patient.city)
        else:
            city_index = -1

        
        new_patient[0] = int(patient.gender == "male")       
        new_patient[1] = patient.age   
        new_patient[2] = city_index
        new_patient[3] = patient.body_height       
        new_patient[4] = patient.body_mass_index   
        new_patient[5] = patient.body_weight 
        new_patient[6] = patient.hemoglobin_a1c                      
        new_patient[7] = patient.high_density_lipoprotein_cholesterol
        new_patient[8] = patient.low_density_lipoprotein_cholesterol 
        new_patient[9] = patient.total_cholesterol                   
        new_patient[10] = patient.triglycerides                       
        new_patient[11] = patient.calcium                             
        new_patient[12] = patient.carbon_dioxide                      
        new_patient[13] = patient.chloride                            
        new_patient[14] = patient.creatinine                          
        new_patient[15] = patient.glucose                             
        new_patient[16] = patient.potassium                           
        new_patient[17] = patient.sodium                              
        new_patient[18] = patient.urea_nitrogen                       
        new_patient[19] = patient.glomerular_filtration               
        new_patient[20] = patient.microalbumin                        
        new_patient[21] = patient.fev1_fvc    
        

        df2 = pd.DataFrame({self.chol_df.columns[i]: new_patient[i]} for i in range(22)).iloc[0]
        temp_df = pd.concat([self.chol_df, df2], ignore_index = True, axis = 0).iloc[0:-21][self.chol_df.columns[0:]]
        imputer = KNNImputer(n_neighbors=5, weights="distance")
        arr = imputer.fit_transform(temp_df)
        temp_df = pd.DataFrame(arr, columns = self.chol_df.columns)
        new_patient = temp_df.iloc[-1]
        new_patient = np.array([new_patient])

        #print(df2.columns)

        estimation = self.chol_model.predict(new_patient)
        print("ESTIMATION : ", estimation)

        if estimation[0][3] < 3:
            patient.cholesterol_risk = "Cholesterol level is normal."

        elif estimation[0][3] < 4:
            patient.cholesterol_risk = "Patient has tendencies to heart disease risk."

        else:
            patient.cholesterol_risk = "Patient most likely has a heart disease risk."


        return patient

