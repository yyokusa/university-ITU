
class CountryHdiModel:
    def __init__(self,
                 name,
                 hdi_rank,
                 country_id,
                 hd_id,
                 hdi,
                 life,
                 education_e,
                 education_m,
                 gnhd,
                 gni,):
        self.name = name
        self.hdi_rank = hdi_rank
        self.country_id = country_id
        self.hd_id = hd_id
        self.hdi = hdi
        self.life = life
        self.education_e = education_e
        self.education_m = education_m
        self.gnhd = gnhd
        self.gni = gni
