# Beacon Class
# koki 15072015

class Beacon:

	""" private vars """
	uuid = "N/A"
	macs = []
	major = 0
	minor = 0
	txpower = 0
	rssi = 0

	def __init__(self,uuid,mac,major,minor,txpower,rssi):
		self.uuid = uuid
		self.macs = []
		self.macs.append(mac);
		self.major = major
		self.minor = minor
		self.txpower = txpower
		self.rssi = rssi

	def __str__(self):
		string = "-------------\n"
		string += "\tUDID: " + self.uuid
		string += "\tMAJOR: " + str(self.major)
		string += "\tMINOR: " + str(self.minor)
		string += "\tDIST: " + str(self.getDistance())
		#string += "\t(Unknown): " + str(self.txpower)
		#string += "\tRSSI:" + str(self.rssi)
		string += "\tMAC address: "
		if len(self.macs) > 1:
			string += str(len(self.macs))
		else:
			string += self.macs[0]

		return string

	def addMACadr(self,mac):
		if any(mac in s for s in self.macs):
			pass
		else:
			self.macs.append(mac)

	def updateData(self,txp,rssi):
		self.txp = txp
		self.rssi = rssi


	def getDistance(self):
		if self.rssi == 0:
			return -1.0

		#print type(self.rssi)
		if self.txpower == 0:
			return -1.0

		ratio = self.rssi * 1.0 / self.txpower
		if ratio < 1.0:
			return ratio**10
		else:
			return 0.89976*ratio**7.7095 + 0.111
