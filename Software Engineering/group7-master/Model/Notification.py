class Notification:
    def __init__(self, notif_id, email, name, surname, status, _from, to):
        self.email = email
        self.name = name
        self.surname = surname
        self._from = _from
        self.to = to
        self.id = notif_id
        self.status = status
