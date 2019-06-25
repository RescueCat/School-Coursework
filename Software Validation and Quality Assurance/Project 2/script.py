import sys
import time
import subprocess
from com.android.monkeyrunner import MonkeyRunner, MonkeyDevice

subprocess.call("..\\..\\platform-tools\\adb.exe logcat -c", shell=True)
device = MonkeyRunner.waitForConnection()

# Launch contacts application from home screen
device.startActivity(component='com.android.contacts/.activities.PeopleActivity')
time.sleep(2)

# Add contact
device.touch(950, 1700, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Make the contact local (if dialog box appears)
device.touch(310, 1060, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Add a name
device.touch(520, 1030, MonkeyDevice.DOWN_AND_UP)
device.type('John')
time.sleep(2)
# Add a phone number, set to home
device.touch(505, 1186, MonkeyDevice.DOWN_AND_UP)
device.type('12345678900')
time.sleep(2)
# Add an email
device.touch(540, 1750, MonkeyDevice.DOWN_AND_UP)
device.type('someemail@email.com')
time.sleep(3)
# Approve new contact
device.touch(1013, 133, MonkeyDevice.DOWN_AND_UP)
time.sleep(5)

# Accept Storage Settings (if dialog box appears)
device.touch(804, 1042, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
device.touch(804, 1042, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
device.touch(804, 1042, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Favorite the contact
device.touch(787, 138, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Edit contact with intent of saving
device.touch(914, 135, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Change Name
device.touch(520, 1000, MonkeyDevice.DOWN_AND_UP)
device.type('athan')
time.sleep(2)
# change phone number
device.touch(540, 1174, MonkeyDevice.DOWN_AND_UP)
device.press('KEYCODE_DEL', MonkeyDevice.DOWN_AND_UP)
device.type('9')
time.sleep(2)
# change email
device.touch(640, 1742, MonkeyDevice.DOWN_AND_UP)
device.press('KEYCODE_DEL', MonkeyDevice.DOWN_AND_UP)
device.type('s')
time.sleep(2)
# change the phone type
device.touch(507, 1295, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
device.touch(507, 1295, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# commit changes
device.touch(906, 139, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Edit contact with intent of discarding
device.touch(914, 135, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Change Name
device.touch(520, 1000, MonkeyDevice.DOWN_AND_UP)
device.press('KEYCODE_DEL', MonkeyDevice.DOWN_AND_UP)
device.type('athan')
time.sleep(2)
# change phone number
device.touch(540, 1174, MonkeyDevice.DOWN_AND_UP)
device.press('KEYCODE_DEL', MonkeyDevice.DOWN_AND_UP)
device.type('1')
time.sleep(2)
# change email
device.touch(640, 1742, MonkeyDevice.DOWN_AND_UP)
device.press('KEYCODE_DEL', MonkeyDevice.DOWN_AND_UP)
device.type('m')
time.sleep(2)
# change the phone type
device.touch(507, 1295, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
device.touch(507, 1295, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# back out
device.touch(70, 139, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# discard changes
device.touch(775, 997, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Go to main Contacts menu
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Access Contacts to Display Function
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Tap Contacts to Display Option
device.touch(772, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'All Contacts'
device.touch(526, 292, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Import Contacts
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Import/Export' Option
device.touch(772, 267, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Import from Sim'
device.touch(503, 933, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Exit NOTE: THERE WILL BE NO CONTACTS ON SIM
device.touch(65, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

'''# Export Contacts
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Import/Export' Option
device.touch(772, 267, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'export to .vcf'
device.touch(515, 1060, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Allow
device.touch(789, 1086, MonkeyDevice.DOWN_AND_UP)
time.sleep(5)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)'''

# Block a number
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Block Numbers'
device.touch(783, 392, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Add number'
device.touch(148, 493, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Type number to block
device.type('2104109970')
time.sleep(3)
# Choose 'Block'
device.touch(896, 1109, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Remove blocked number
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Block Numbers'
device.touch(783, 392, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Click the 'x'
device.touch(973, 635, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose unblock
device.touch(862, 990, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Explore 'Manage Accounts' option
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Manage Accounts'
device.touch(795, 516, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)


#Explore 'Settings'
# Change 'Sort by' to 'Last'
# Tap menu
device.touch(1023, 136, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Settings'
device.touch(762, 645, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Select 'Sort By'
device.touch(500, 337, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Select 'By last name'
device.touch(465, 1050, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Rest 'Sort by' to default
# Select 'Sort By'
device.touch(500, 337, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Select 'By first name'
device.touch(500, 923, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Change 'Name Format'
# Select 'Name Format'
device.touch(482, 505, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'Last Name First'
device.touch(584, 1065, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Rest 'Name Format' to default
# Select 'Name Format'
device.touch(482, 505, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
# Choose 'First Name First'
device.touch(562, 933, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Explore About Contacts
# Select "About Contacts'
device.touch(493, 668, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# View 'Open Source License'
device.touch(470, 514, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# View 'Privacy Policy'
device.touch(547, 676, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# View 'Terms of Service'
device.touch(559, 821, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Exit
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Exit 'Settings'
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Profile
# Create Profile
device.touch(500, 500, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Add a name
device.touch(520, 1030, MonkeyDevice.DOWN_AND_UP)
device.type('Andrew')
time.sleep(2)
# Add a phone number, set to home
device.touch(505, 1186, MonkeyDevice.DOWN_AND_UP)
device.type('10098765432')
time.sleep(2)
# Add an email
device.touch(540, 1750, MonkeyDevice.DOWN_AND_UP)
device.type('someemail@email.com')
time.sleep(3)
# Approve Profile Settings
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(2)
device.touch(775, 997, MonkeyDevice.DOWN_AND_UP)
time.sleep(2)

# Option only shows up sometimes, opted out of testing this
# Add number to existing profile
# Add contact
# device.touch(950, 1700, MonkeyDevice.DOWN_AND_UP)
# time.sleep(2)
# Add a phone number, set to home
# device.touch(505, 1186, MonkeyDevice.DOWN_AND_UP)
# device.type('4444444444')
# time.sleep(2)
# Add an email
# device.touch(540, 1750, MonkeyDevice.DOWN_AND_UP)
# device.type('important@email.com')
# time.sleep(3)
# Add a name
# device.touch(520, 1030, MonkeyDevice.DOWN_AND_UP)
# device.type('Andrew')
# time.sleep(2)
# Select existing profile
# device.touch(553, 1136, MonkeyDevice.DOWN_AND_UP)
# time.sleep(2)
# Select ok
# device.touch(795, 1030, MonkeyDevice.DOWN_AND_UP)
# time.sleep(2)
# Approve
# device.touch(900, 130, MonkeyDevice.DOWN_AND_UP)
# time.sleep(2)
# Exit Edit
# device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
# time.sleep(2)

# Contact Detail Options
# Call Contact
device.touch(432, 656, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Make the Call
device.touch(612, 1276, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Close the Call
device.touch(551, 1592, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Message the contact
device.touch(975, 1272, MonkeyDevice.DOWN_AND_UP)
time.sleep(5)
# Return to contacts
device.touch(846, 1863, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
device.touch(846, 1863, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Exit 'Contact Detail'
device.press('KEYCODE_BACK', MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Delete Contact
# Choose Contact
device.touch(432, 656, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Choose Options
device.touch(1023, 133, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Choose Delete
device.touch(790, 125, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
# Confirm
device.touch(670, 996, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

# Exit Contacts App
device.touch(846, 1863, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
device.touch(960, 371, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)
device.touch(960, 371, MonkeyDevice.DOWN_AND_UP)
time.sleep(3)

subprocess.call("..\\..\\platform-tools\\adb.exe logcat -d > log.txt", shell=True)
# subprocess.call("taskkill /f /im adb.exe", shell=True)
