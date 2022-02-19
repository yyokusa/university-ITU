
class HDIModel:
    def __init__(self,
                 country_id,
                 hdi,
                 life,
                 education_e,
                 education_m,
                 gnhd,
                 gni,
                 _id=None):
        self.country_id = country_id
        self.hdi = hdi
        self.life = life
        self.education_e = education_e
        self.education_m = education_m
        self.gnhd = gnhd
        self.gni = gni
        self.id = _id
